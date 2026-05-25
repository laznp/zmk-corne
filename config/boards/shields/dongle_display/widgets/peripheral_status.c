/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/ble.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/event_manager.h>

#include "peripheral_status.h"

#ifndef ZMK_SPLIT_BLE_PERIPHERAL_COUNT
#  define ZMK_SPLIT_BLE_PERIPHERAL_COUNT 0
#endif

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct peripheral_state {
    uint8_t source;
    uint8_t state_of_charge;
    bool has_data;
};

static lv_obj_t *battery_labels[ZMK_SPLIT_BLE_PERIPHERAL_COUNT];

static void set_status(lv_obj_t *widget, struct peripheral_state state) {
    if (state.source >= ZMK_SPLIT_BLE_PERIPHERAL_COUNT) {
        return;
    }
    if (!state.has_data) {
        lv_label_set_text(battery_labels[state.source], "--");
    } else {
        char buf[4];
        snprintf(buf, sizeof(buf), "%d", state.state_of_charge);
        lv_label_set_text(battery_labels[state.source], buf);
    }
}

static void peripheral_status_update_cb(struct peripheral_state state) {
    struct zmk_widget_peripheral_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_status(widget->obj, state); }
}

static struct peripheral_state peripheral_status_get_state(const zmk_event_t *eh) {
    const struct zmk_peripheral_battery_state_changed *ev = as_zmk_peripheral_battery_state_changed(eh);
    return (struct peripheral_state){
        .source = ev->source,
        .state_of_charge = ev->state_of_charge,
        .has_data = true,
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_peripheral_status, struct peripheral_state,
                            peripheral_status_update_cb, peripheral_status_get_state)

ZMK_SUBSCRIPTION(widget_peripheral_status, zmk_peripheral_battery_state_changed);

int zmk_widget_peripheral_status_init(struct zmk_widget_peripheral_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    for (int i = 0; i < ZMK_SPLIT_BLE_PERIPHERAL_COUNT; i++) {
        battery_labels[i] = lv_label_create(widget->obj);
        lv_label_set_text(battery_labels[i], "--");
        lv_obj_align(battery_labels[i], LV_ALIGN_TOP_RIGHT, 0, i * 10);
    }

    sys_slist_append(&widgets, &widget->node);
    widget_peripheral_status_init();
    return 0;
}

lv_obj_t *zmk_widget_peripheral_status_obj(struct zmk_widget_peripheral_status *widget) {
    return widget->obj;
}
