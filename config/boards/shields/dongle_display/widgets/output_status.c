/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <lvgl.h>

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/usb.h>
#include <zmk/endpoints.h>

#include "output_status.h"
#if IS_ENABLED(CONFIG_ZMK_BLE)
#  include <zmk/events/ble_active_profile_changed.h>
#  include <zmk/ble.h>
#endif

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct output_status_state {
    struct zmk_endpoint_instance selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
    bool usb_is_hid_ready;
};

static struct output_status_state get_state(const zmk_event_t *_eh) {
    struct output_status_state st;
    st.selected_endpoint = zmk_endpoints_selected();
#if IS_ENABLED(CONFIG_ZMK_BLE)
    st.active_profile_index     = zmk_ble_active_profile_index();
    st.active_profile_connected = zmk_ble_active_profile_is_connected();
    st.active_profile_bonded    = !zmk_ble_active_profile_is_open();
#else
    st.active_profile_index     = 0;
    st.active_profile_connected = false;
    st.active_profile_bonded    = false;
#endif
    st.usb_is_hid_ready = zmk_usb_is_hid_ready();
    return st;
}

static void set_status_symbol(lv_obj_t *label, struct output_status_state state) {
    char text[20] = {};

    switch (state.selected_endpoint.transport) {
    case ZMK_TRANSPORT_USB:
        strcat(text, LV_SYMBOL_USB);
        if (state.usb_is_hid_ready) {
            strcat(text, " " LV_SYMBOL_OK);
        } else {
            strcat(text, " " LV_SYMBOL_CLOSE);
        }
        break;
    case ZMK_TRANSPORT_BLE:
        if (state.active_profile_bonded) {
            if (state.active_profile_connected) {
                snprintf(text, sizeof(text), LV_SYMBOL_WIFI " %i " LV_SYMBOL_OK,
                         state.active_profile_index + 1);
            } else {
                snprintf(text, sizeof(text), LV_SYMBOL_WIFI " %i " LV_SYMBOL_CLOSE,
                         state.active_profile_index + 1);
            }
        } else {
            snprintf(text, sizeof(text), LV_SYMBOL_WIFI " %i " LV_SYMBOL_SETTINGS,
                     state.active_profile_index + 1);
        }
        break;
    }

    lv_label_set_text(label, text);
}

static void output_status_update_cb(struct output_status_state state) {
    struct zmk_widget_output_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_status_symbol(widget->obj, state); }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_output_status, struct output_status_state,
                            output_status_update_cb, get_state)
ZMK_SUBSCRIPTION(widget_output_status, zmk_endpoint_changed);
#if IS_ENABLED(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(widget_output_status, zmk_ble_active_profile_changed);
#endif
ZMK_SUBSCRIPTION(widget_output_status, zmk_usb_conn_state_changed);

int zmk_widget_output_status_init(struct zmk_widget_output_status *widget, lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);
    sys_slist_append(&widgets, &widget->node);
    widget_output_status_init();
    return 0;
}

lv_obj_t *zmk_widget_output_status_obj(struct zmk_widget_output_status *widget) {
    return widget->obj;
}
