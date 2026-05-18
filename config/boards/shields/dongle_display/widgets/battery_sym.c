/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <lvgl.h>

/* Battery icon images — indexed 1-bit, 5x8 pixels.
 * Depletion indicator: MORE fill = LESS battery remaining.
 * Palette: index 0 = background (white), index 1 = foreground (black/ON).
 */

/* Level 0: no fill (battery > 90%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_EMPTY
#define LV_ATTRIBUTE_IMG_BATT_EMPTY
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_EMPTY
uint8_t batt_empty_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x88, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,
};

const lv_img_dsc_t batt_empty = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_empty_map,
};

/* Level 1: fill row 2 (battery 71-90%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_L1
#define LV_ATTRIBUTE_IMG_BATT_L1
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_L1
uint8_t batt_l1_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x70,
};

const lv_img_dsc_t batt_l1 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_l1_map,
};

/* Level 2: fill rows 2-3 (battery 51-70%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_L2
#define LV_ATTRIBUTE_IMG_BATT_L2
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_L2
uint8_t batt_l2_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0xF8, 0xF8, 0x88, 0x88, 0x88, 0x70,
};

const lv_img_dsc_t batt_l2 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_l2_map,
};

/* Level 3: fill rows 2-4 (battery 31-50%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_L3
#define LV_ATTRIBUTE_IMG_BATT_L3
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_L3
uint8_t batt_l3_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0xF8, 0xF8, 0xF8, 0x88, 0x88, 0x70,
};

const lv_img_dsc_t batt_l3 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_l3_map,
};

/* Level 4: fill rows 2-5 (battery 11-30%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_L4
#define LV_ATTRIBUTE_IMG_BATT_L4
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_L4
uint8_t batt_l4_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0xF8, 0xF8, 0xF8, 0xF8, 0x88, 0x70,
};

const lv_img_dsc_t batt_l4 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_l4_map,
};

/* Level 5: fill rows 2-6 (battery 0-10%) */
#ifndef LV_ATTRIBUTE_IMG_BATT_L5
#define LV_ATTRIBUTE_IMG_BATT_L5
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_L5
uint8_t batt_l5_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x70,
};

const lv_img_dsc_t batt_l5 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_l5_map,
};

/* USB mode: hollow fill area (border only, no interior) */
#ifndef LV_ATTRIBUTE_IMG_BATT_USB
#define LV_ATTRIBUTE_IMG_BATT_USB
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATT_USB
uint8_t batt_usb_map[] = {
  0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff,

  0x88, 0x70, 0x70, 0x50, 0x50, 0x50, 0x70, 0x70,
};

const lv_img_dsc_t batt_usb = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 5,
  .header.h = 8,
  .data_size = 16,
  .data = batt_usb_map,
};
