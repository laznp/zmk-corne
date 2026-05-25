/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "custom_status_screen.h"
#include "widgets/output_status.h"
#include "widgets/hid_indicators.h"
#include "widgets/wpm_status.h"

#include <zmk/display.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/keymap.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static struct zmk_widget_output_status output_status_widget;

#if IS_ENABLED(CONFIG_ZMK_HID_INDICATORS)
static struct zmk_widget_hid_indicators hid_indicators_widget;
#endif

#if IS_ENABLED(CONFIG_ZMK_DONGLE_DISPLAY_WPM)
static struct zmk_widget_wpm_status wpm_status_widget;
#endif

static lv_obj_t *layer_label;

static void update_layer_label(void) {
    uint8_t index = zmk_keymap_highest_layer_active();
    const char *name = zmk_keymap_layer_name(index);
    if (name != NULL) {
        lv_label_set_text(layer_label, name);
    } else {
        char buf[4];
        snprintf(buf, sizeof(buf), "%d", index);
        lv_label_set_text(layer_label, buf);
    }
}

static int layer_event_handler(const zmk_event_t *eh) {
    update_layer_label();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_status_screen, layer_event_handler);
ZMK_SUBSCRIPTION(layer_status_screen, zmk_layer_state_changed);

lv_style_t global_style;

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;

    screen = lv_obj_create(NULL);

    lv_style_init(&global_style);
    lv_style_set_bg_color(&global_style, lv_color_white());
    lv_style_set_bg_opa(&global_style, LV_OPA_COVER);
    lv_style_set_text_color(&global_style, lv_color_black());
    lv_style_set_text_font(&global_style, &lv_font_unscii_8);
    lv_style_set_text_letter_space(&global_style, 1);
    lv_style_set_text_line_space(&global_style, 1);
    lv_obj_add_style(screen, &global_style, LV_PART_MAIN);

    /*
     * Landscape 128x32 layout:
     *
     * [output_status][  Laz  ][layer]
     */

    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *label_mid = lv_label_create(screen);
    lv_label_set_text(label_mid, "Laz");
    lv_obj_align(label_mid, LV_ALIGN_CENTER, 0, 0);

    layer_label = lv_label_create(screen);
    lv_label_set_text(layer_label, "0");
    lv_obj_align(layer_label, LV_ALIGN_RIGHT_MID, -2, 0);

#if IS_ENABLED(CONFIG_ZMK_DONGLE_DISPLAY_WPM)
    zmk_widget_wpm_status_init(&wpm_status_widget, screen);
    lv_obj_align(zmk_widget_wpm_status_obj(&wpm_status_widget), LV_ALIGN_TOP_LEFT, 22, 0);
#endif

#if IS_ENABLED(CONFIG_ZMK_HID_INDICATORS)
    zmk_widget_hid_indicators_init(&hid_indicators_widget, screen);
    lv_obj_align(zmk_widget_hid_indicators_obj(&hid_indicators_widget), LV_ALIGN_BOTTOM_LEFT, 22, 0);
#endif

    return screen;
}
