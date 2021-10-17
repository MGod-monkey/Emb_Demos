/*
 * @Author: your name
 * @Date: 2021-10-08 19:04:18
 * @LastEditTime: 2021-10-10 17:21:14
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\src\assets\battery_01.c
 */
#include "lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_BATTERY_01
#define LV_ATTRIBUTE_IMG_BATTERY_01
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATTERY_01 uint8_t battery_01_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Blue: 2 bit, Green: 3 bit, Red: 3 bit, Alpha 8 bit */
  0x00, 0xff, 0x00, 0xff, 0x24, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x49, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x00, 0xff, 0x29, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x24, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xfb, 0xff, 0xdb, 0xff, 0xfb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x49, 0xff, 0x00, 0xff, 0x04, 0xff, 0x00, 0xff, 0x00, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x92, 0xff, 0xff, 0xff, 0x92, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x44, 0xff, 0x85, 0xff, 0x85, 0xff, 0x65, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xdb, 0xff, 0x92, 0xff, 0x49, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x85, 0xff, 0xee, 0xff, 0xed, 0xff, 0xc9, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x85, 0xff, 0xed, 0xff, 0xcd, 0xff, 0xa9, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x64, 0xff, 0xed, 0xff, 0xe9, 0xff, 0xa9, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x85, 0xff, 0xee, 0xff, 0xed, 0xff, 0xc9, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0xff, 0x44, 0xff, 0x89, 0xff, 0x89, 0xff, 0x65, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0xdb, 0xff, 0x92, 0xff, 0x49, 0xff, 0x00, 0xff, 
  0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0x49, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x92, 0xff, 0xff, 0xff, 0x92, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x24, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x00, 0xff, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
  0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x24, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Blue: 5 bit, Green: 6 bit, Red: 5 bit, Alpha 8 bit*/
  0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x04, 0x21, 0xff, 0x0b, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x2c, 0x63, 0xff, 0x0c, 0x6b, 0xff, 0x2c, 0x5b, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x2c, 0x63, 0xff, 0x08, 0x42, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0xc6, 0x31, 0xff, 0x17, 0xc6, 0xff, 0x9e, 0xf7, 0xff, 0xbf, 0xff, 0xff, 0xbe, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xde, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbe, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x5d, 0xef, 0xff, 0xf0, 0x83, 0xff, 0x41, 0x08, 0xff, 0x00, 0x00, 0xff, 0x20, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0xc3, 0x18, 0xff, 0xf7, 0xbd, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xde, 0xff, 0x7a, 0xce, 0xff, 0x9a, 0xd6, 0xff, 0x99, 0xd6, 0xff, 0x79, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x79, 0xd6, 0xff, 0x79, 0xce, 0xff, 0x79, 0xce, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x7a, 0xd6, 0xff, 0x9a, 0xd6, 0xff, 0x79, 0xce, 0xff, 0x9e, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x0c, 0x63, 0xff, 0x20, 0x00, 0xff, 0x21, 0x08, 0xff, 0x00, 0x00, 0xff, 
  0x28, 0x4a, 0xff, 0x5e, 0xef, 0xff, 0x1c, 0xe7, 0xff, 0x29, 0x4a, 0xff, 0x62, 0x08, 0xff, 0x82, 0x08, 0xff, 0x42, 0x08, 0xff, 0x83, 0x08, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xa3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xa3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xa3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xa2, 0x10, 0xff, 0xa3, 0x18, 0xff, 0xa2, 0x10, 0xff, 0xa2, 0x10, 0xff, 0x92, 0x94, 0xff, 0xff, 0xff, 0xff, 0x30, 0x84, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x28, 0x4a, 0xff, 0x5d, 0xef, 0xff, 0xfb, 0xde, 0xff, 0x24, 0x21, 0xff, 0xa2, 0x40, 0xff, 0x86, 0x89, 0xff, 0x86, 0x81, 0xff, 0x04, 0x69, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xcf, 0x7b, 0xff, 0xff, 0xff, 0xff, 0xd7, 0xbd, 0xff, 0xf0, 0x83, 0xff, 0x08, 0x42, 0xff, 0x00, 0x00, 0xff, 
  0x29, 0x4a, 0xff, 0x3d, 0xef, 0xff, 0x1c, 0xe7, 0xff, 0x45, 0x21, 0xff, 0x45, 0x79, 0xff, 0x2c, 0xfb, 0xff, 0xeb, 0xea, 0xff, 0x29, 0xc2, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x21, 0x08, 0xff, 0x00, 0x00, 0xff, 0x30, 0x84, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0xe7, 0xff, 0x41, 0x08, 0xff, 
  0x49, 0x4a, 0xff, 0x5d, 0xef, 0xff, 0x1c, 0xe7, 0xff, 0x25, 0x29, 0xff, 0x05, 0x71, 0xff, 0xeb, 0xe2, 0xff, 0x89, 0xd2, 0xff, 0x08, 0xaa, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x10, 0x84, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x62, 0x10, 0xff, 
  0x28, 0x4a, 0xff, 0x7d, 0xef, 0xff, 0xfc, 0xe6, 0xff, 0x45, 0x21, 0xff, 0x24, 0x69, 0xff, 0xcb, 0xe2, 0xff, 0x8b, 0xda, 0xff, 0x08, 0xaa, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x30, 0x84, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x82, 0x10, 0xff, 
  0x29, 0x4a, 0xff, 0x5d, 0xef, 0xff, 0x1c, 0xef, 0xff, 0x45, 0x19, 0xff, 0x45, 0x81, 0xff, 0x0c, 0xfb, 0xff, 0xec, 0xf2, 0xff, 0x4a, 0xc2, 0xff, 0x20, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x08, 0xff, 0x20, 0x00, 0xff, 0x21, 0x00, 0xff, 0x20, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x20, 0x00, 0xff, 0x00, 0x00, 0xff, 0x30, 0x84, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xef, 0xff, 0x41, 0x08, 0xff, 
  0x29, 0x4a, 0xff, 0x5d, 0xef, 0xff, 0xfc, 0xe6, 0xff, 0x25, 0x29, 0xff, 0xa2, 0x40, 0xff, 0xa6, 0x89, 0xff, 0x86, 0x81, 0xff, 0x24, 0x69, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xcf, 0x7b, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc5, 0xff, 0x51, 0x8c, 0xff, 0x49, 0x4a, 0xff, 0x00, 0x00, 0xff, 
  0x29, 0x4a, 0xff, 0x5d, 0xef, 0xff, 0x3d, 0xe7, 0xff, 0x08, 0x42, 0xff, 0x40, 0x00, 0xff, 0x21, 0x00, 0xff, 0x40, 0x00, 0xff, 0x41, 0x00, 0xff, 0x82, 0x10, 0xff, 0x82, 0x10, 0xff, 0x62, 0x10, 0xff, 0x82, 0x10, 0xff, 0x62, 0x10, 0xff, 0x82, 0x10, 0xff, 0x62, 0x10, 0xff, 0x82, 0x10, 0xff, 0x82, 0x10, 0xff, 0x62, 0x10, 0xff, 0x82, 0x10, 0xff, 0x82, 0x10, 0xff, 0x62, 0x10, 0xff, 0x71, 0x8c, 0xff, 0xff, 0xff, 0xff, 0x30, 0x84, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0xe4, 0x18, 0xff, 0x18, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xba, 0xde, 0xff, 0x17, 0xc6, 0xff, 0x39, 0xce, 0xff, 0x38, 0xc6, 0xff, 0x38, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x38, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x38, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0x18, 0xc6, 0xff, 0xf8, 0xc5, 0xff, 0x7d, 0xef, 0xff, 0xff, 0xff, 0xff, 0x4d, 0x6b, 0xff, 0x00, 0x00, 0xff, 0x41, 0x08, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0xc7, 0x39, 0xff, 0xba, 0xd6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x71, 0x8c, 0xff, 0x61, 0x08, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x20, 0x08, 0xff, 0xc3, 0x18, 0xff, 0xe3, 0x18, 0xff, 0xc2, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc4, 0x20, 0xff, 0xc3, 0x20, 0xff, 0xe3, 0x18, 0xff, 0xe3, 0x18, 0xff, 0xe4, 0x18, 0xff, 0xc3, 0x20, 0xff, 0xc3, 0x18, 0xff, 0xe4, 0x18, 0xff, 0xe3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0xc3, 0x18, 0xff, 0x82, 0x10, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format:  Blue: 5 bit Green: 6 bit, Red: 5 bit, Alpha 8 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x21, 0x04, 0xff, 0x63, 0x0b, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x2c, 0xff, 0x6b, 0x0c, 0xff, 0x5b, 0x2c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x2c, 0xff, 0x42, 0x08, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0x31, 0xc6, 0xff, 0xc6, 0x17, 0xff, 0xf7, 0x9e, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xbe, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xde, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbe, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xbf, 0xff, 0xef, 0x5d, 0xff, 0x83, 0xf0, 0xff, 0x08, 0x41, 0xff, 0x00, 0x00, 0xff, 0x00, 0x20, 0xff, 0x00, 0x00, 0xff, 
  0x18, 0xc3, 0xff, 0xbd, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0xff, 0xce, 0x7a, 0xff, 0xd6, 0x9a, 0xff, 0xd6, 0x99, 0xff, 0xd6, 0x79, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x79, 0xff, 0xce, 0x79, 0xff, 0xce, 0x79, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x7a, 0xff, 0xd6, 0x9a, 0xff, 0xce, 0x79, 0xff, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0x63, 0x0c, 0xff, 0x00, 0x20, 0xff, 0x08, 0x21, 0xff, 0x00, 0x00, 0xff, 
  0x4a, 0x28, 0xff, 0xef, 0x5e, 0xff, 0xe7, 0x1c, 0xff, 0x4a, 0x29, 0xff, 0x08, 0x62, 0xff, 0x08, 0x82, 0xff, 0x08, 0x42, 0xff, 0x08, 0x83, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xa3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xa3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xa3, 0xff, 0x18, 0xc3, 0xff, 0x10, 0xa2, 0xff, 0x18, 0xa3, 0xff, 0x10, 0xa2, 0xff, 0x10, 0xa2, 0xff, 0x94, 0x92, 0xff, 0xff, 0xff, 0xff, 0x84, 0x30, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x4a, 0x28, 0xff, 0xef, 0x5d, 0xff, 0xde, 0xfb, 0xff, 0x21, 0x24, 0xff, 0x40, 0xa2, 0xff, 0x89, 0x86, 0xff, 0x81, 0x86, 0xff, 0x69, 0x04, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x7b, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xd7, 0xff, 0x83, 0xf0, 0xff, 0x42, 0x08, 0xff, 0x00, 0x00, 0xff, 
  0x4a, 0x29, 0xff, 0xef, 0x3d, 0xff, 0xe7, 0x1c, 0xff, 0x21, 0x45, 0xff, 0x79, 0x45, 0xff, 0xfb, 0x2c, 0xff, 0xea, 0xeb, 0xff, 0xc2, 0x29, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x08, 0x21, 0xff, 0x00, 0x00, 0xff, 0x84, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x3c, 0xff, 0x08, 0x41, 0xff, 
  0x4a, 0x49, 0xff, 0xef, 0x5d, 0xff, 0xe7, 0x1c, 0xff, 0x29, 0x25, 0xff, 0x71, 0x05, 0xff, 0xe2, 0xeb, 0xff, 0xd2, 0x89, 0xff, 0xaa, 0x08, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x62, 0xff, 
  0x4a, 0x28, 0xff, 0xef, 0x7d, 0xff, 0xe6, 0xfc, 0xff, 0x21, 0x45, 0xff, 0x69, 0x24, 0xff, 0xe2, 0xcb, 0xff, 0xda, 0x8b, 0xff, 0xaa, 0x08, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x84, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0x10, 0x82, 0xff, 
  0x4a, 0x29, 0xff, 0xef, 0x5d, 0xff, 0xef, 0x1c, 0xff, 0x19, 0x45, 0xff, 0x81, 0x45, 0xff, 0xfb, 0x0c, 0xff, 0xf2, 0xec, 0xff, 0xc2, 0x4a, 0xff, 0x00, 0x20, 0xff, 0x00, 0x00, 0xff, 0x08, 0x00, 0xff, 0x00, 0x20, 0xff, 0x00, 0x21, 0xff, 0x00, 0x20, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x20, 0xff, 0x00, 0x00, 0xff, 0x84, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xef, 0x7d, 0xff, 0x08, 0x41, 0xff, 
  0x4a, 0x29, 0xff, 0xef, 0x5d, 0xff, 0xe6, 0xfc, 0xff, 0x29, 0x25, 0xff, 0x40, 0xa2, 0xff, 0x89, 0xa6, 0xff, 0x81, 0x86, 0xff, 0x69, 0x24, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x7b, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xc5, 0xf8, 0xff, 0x8c, 0x51, 0xff, 0x4a, 0x49, 0xff, 0x00, 0x00, 0xff, 
  0x4a, 0x29, 0xff, 0xef, 0x5d, 0xff, 0xe7, 0x3d, 0xff, 0x42, 0x08, 0xff, 0x00, 0x40, 0xff, 0x00, 0x21, 0xff, 0x00, 0x40, 0xff, 0x00, 0x41, 0xff, 0x10, 0x82, 0xff, 0x10, 0x82, 0xff, 0x10, 0x62, 0xff, 0x10, 0x82, 0xff, 0x10, 0x62, 0xff, 0x10, 0x82, 0xff, 0x10, 0x62, 0xff, 0x10, 0x82, 0xff, 0x10, 0x82, 0xff, 0x10, 0x62, 0xff, 0x10, 0x82, 0xff, 0x10, 0x82, 0xff, 0x10, 0x62, 0xff, 0x8c, 0x71, 0xff, 0xff, 0xff, 0xff, 0x84, 0x30, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x18, 0xe4, 0xff, 0xc6, 0x18, 0xff, 0xff, 0xff, 0xff, 0xde, 0xba, 0xff, 0xc6, 0x17, 0xff, 0xce, 0x39, 0xff, 0xc6, 0x38, 0xff, 0xc6, 0x38, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x38, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x38, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc6, 0x18, 0xff, 0xc5, 0xf8, 0xff, 0xef, 0x7d, 0xff, 0xff, 0xff, 0xff, 0x6b, 0x4d, 0xff, 0x00, 0x00, 0xff, 0x08, 0x41, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0x39, 0xc7, 0xff, 0xd6, 0xba, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x71, 0xff, 0x08, 0x61, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x08, 0x20, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xe3, 0xff, 0x18, 0xc2, 0xff, 0x18, 0xc3, 0xff, 0x20, 0xc4, 0xff, 0x20, 0xc3, 0xff, 0x18, 0xe3, 0xff, 0x18, 0xe3, 0xff, 0x18, 0xe4, 0xff, 0x20, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xe4, 0xff, 0x18, 0xe3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x18, 0xc3, 0xff, 0x10, 0x82, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format:  Blue: 8 bit, Green: 8 bit, Red: 8 bit, Alpha: 8 bit*/
  0x04, 0x02, 0x02, 0xff, 0x00, 0x00, 0x01, 0xff, 0x1e, 0x1f, 0x1d, 0xff, 0x59, 0x5f, 0x5e, 0xff, 0x61, 0x5f, 0x5e, 0xff, 0x62, 0x63, 0x5f, 0xff, 0x61, 0x5f, 0x65, 0xff, 0x5e, 0x63, 0x5a, 0xff, 0x60, 0x61, 0x5f, 0xff, 0x60, 0x60, 0x60, 0xff, 0x61, 0x61, 0x61, 0xff, 0x5e, 0x60, 0x60, 0xff, 0x5e, 0x60, 0x60, 0xff, 0x62, 0x62, 0x62, 0xff, 0x60, 0x60, 0x60, 0xff, 0x60, 0x60, 0x60, 0xff, 0x60, 0x60, 0x60, 0xff, 0x62, 0x62, 0x62, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x60, 0x60, 0x60, 0xff, 0x64, 0x64, 0x64, 0xff, 0x41, 0x41, 0x41, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 
  0x02, 0x00, 0x00, 0xff, 0x2f, 0x37, 0x30, 0xff, 0xbc, 0xc0, 0xc1, 0xff, 0xed, 0xf1, 0xf2, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xf3, 0xf5, 0xf6, 0xff, 0xf7, 0xf8, 0xf6, 0xff, 0xf4, 0xf8, 0xf9, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf5, 0xf7, 0xf7, 0xff, 0xf4, 0xf6, 0xf6, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xe9, 0xe9, 0xe9, 0xff, 0x7e, 0x7e, 0x7e, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x01, 0x01, 0x01, 0xff, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x18, 0x18, 0x18, 0xff, 0xbc, 0xbd, 0xb9, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xd6, 0xdb, 0xdc, 0xff, 0xcd, 0xcb, 0xcb, 0xff, 0xce, 0xd0, 0xd1, 0xff, 0xcb, 0xcf, 0xd0, 0xff, 0xcb, 0xce, 0xd2, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xce, 0xce, 0xce, 0xff, 0xce, 0xce, 0xce, 0xff, 0xcb, 0xcd, 0xcd, 0xff, 0xca, 0xcc, 0xcc, 0xff, 0xcc, 0xcc, 0xcc, 0xff, 0xce, 0xce, 0xce, 0xff, 0xce, 0xce, 0xce, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xce, 0xce, 0xce, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0xcf, 0xcf, 0xcf, 0xff, 0xcb, 0xcb, 0xcb, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0x61, 0x61, 0x61, 0xff, 0x04, 0x04, 0x04, 0xff, 0x06, 0x06, 0x06, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x3f, 0x44, 0x45, 0xff, 0xed, 0xe9, 0xe8, 0xff, 0xe3, 0xe2, 0xde, 0xff, 0x46, 0x46, 0x46, 0xff, 0x12, 0x0b, 0x08, 0xff, 0x13, 0x11, 0x09, 0xff, 0x0d, 0x0a, 0x05, 0xff, 0x16, 0x0f, 0x06, 0xff, 0x17, 0x17, 0x17, 0xff, 0x18, 0x18, 0x18, 0xff, 0x16, 0x16, 0x16, 0xff, 0x17, 0x17, 0x17, 0xff, 0x17, 0x17, 0x17, 0xff, 0x16, 0x16, 0x16, 0xff, 0x18, 0x18, 0x18, 0xff, 0x16, 0x16, 0x16, 0xff, 0x17, 0x17, 0x17, 0xff, 0x14, 0x14, 0x14, 0xff, 0x16, 0x16, 0x16, 0xff, 0x13, 0x13, 0x13, 0xff, 0x13, 0x13, 0x13, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0x84, 0x84, 0x84, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 
  0x41, 0x45, 0x46, 0xff, 0xe9, 0xe9, 0xe9, 0xff, 0xda, 0xdd, 0xdb, 0xff, 0x22, 0x25, 0x23, 0xff, 0x14, 0x16, 0x3e, 0xff, 0x2d, 0x2f, 0x87, 0xff, 0x2f, 0x30, 0x81, 0xff, 0x23, 0x22, 0x66, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x79, 0x79, 0x79, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xb8, 0xb8, 0xb8, 0xff, 0x7d, 0x7d, 0x7d, 0xff, 0x41, 0x41, 0x41, 0xff, 0x01, 0x01, 0x01, 0xff, 
  0x46, 0x45, 0x47, 0xff, 0xe7, 0xe6, 0xe8, 0xff, 0xdd, 0xe2, 0xe0, 0xff, 0x28, 0x2a, 0x24, 0xff, 0x2a, 0x2a, 0x78, 0xff, 0x62, 0x64, 0xff, 0xff, 0x59, 0x5d, 0xec, 0xff, 0x49, 0x45, 0xc2, 0xff, 0x03, 0x02, 0x04, 0xff, 0x03, 0x02, 0x04, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x00, 0x00, 0x00, 0xff, 0x05, 0x05, 0x05, 0xff, 0x00, 0x00, 0x00, 0xff, 0x83, 0x83, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0x08, 0x08, 0x08, 0xff, 
  0x47, 0x47, 0x47, 0xff, 0xeb, 0xe9, 0xe8, 0xff, 0xdf, 0xe1, 0xe1, 0xff, 0x29, 0x24, 0x25, 0xff, 0x27, 0x22, 0x71, 0xff, 0x56, 0x5b, 0xe0, 0xff, 0x4b, 0x52, 0xcd, 0xff, 0x3f, 0x40, 0xa8, 0xff, 0x01, 0x00, 0x02, 0xff, 0x01, 0x00, 0x02, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 
  0x42, 0x46, 0x47, 0xff, 0xe9, 0xed, 0xe8, 0xff, 0xdd, 0xde, 0xe2, 0xff, 0x2a, 0x27, 0x22, 0xff, 0x1f, 0x24, 0x69, 0xff, 0x57, 0x57, 0xe1, 0xff, 0x58, 0x50, 0xd9, 0xff, 0x3e, 0x40, 0xac, 0xff, 0x01, 0x00, 0x02, 0xff, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x02, 0x02, 0x02, 0xff, 0x00, 0x00, 0x00, 0xff, 0x83, 0x83, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 
  0x45, 0x45, 0x45, 0xff, 0xeb, 0xe8, 0xea, 0xff, 0xe0, 0xe1, 0xe5, 0xff, 0x28, 0x28, 0x1c, 0xff, 0x2b, 0x28, 0x7d, 0xff, 0x62, 0x62, 0xfc, 0xff, 0x60, 0x5d, 0xef, 0xff, 0x4d, 0x49, 0xc0, 0xff, 0x01, 0x03, 0x04, 0xff, 0x03, 0x02, 0x04, 0xff, 0x03, 0x02, 0x06, 0xff, 0x02, 0x04, 0x04, 0xff, 0x05, 0x03, 0x03, 0xff, 0x03, 0x04, 0x02, 0xff, 0x00, 0x02, 0x02, 0xff, 0x04, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x02, 0x02, 0x02, 0xff, 0x03, 0x03, 0x03, 0xff, 0x01, 0x01, 0x01, 0xff, 0x84, 0x84, 0x84, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0x07, 0x07, 0x07, 0xff, 
  0x48, 0x46, 0x46, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xe0, 0xdd, 0xdf, 0xff, 0x29, 0x26, 0x28, 0xff, 0x12, 0x16, 0x3f, 0xff, 0x33, 0x36, 0x87, 0xff, 0x2e, 0x32, 0x81, 0xff, 0x23, 0x24, 0x68, 0xff, 0x00, 0x00, 0x01, 0xff, 0x01, 0x00, 0x02, 0xff, 0x00, 0x00, 0x01, 0xff, 0x00, 0x01, 0x01, 0xff, 0x02, 0x00, 0x00, 0xff, 0x01, 0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x02, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x02, 0x02, 0x02, 0xff, 0x00, 0x00, 0x00, 0xff, 0x7a, 0x7a, 0x7a, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xbe, 0xbe, 0xbe, 0xff, 0x87, 0x87, 0x87, 0xff, 0x47, 0x47, 0x47, 0xff, 0x01, 0x01, 0x01, 0xff, 
  0x46, 0x45, 0x49, 0xff, 0xe6, 0xe8, 0xe9, 0xff, 0xe6, 0xe3, 0xdf, 0xff, 0x44, 0x3f, 0x40, 0xff, 0x03, 0x07, 0x00, 0xff, 0x0b, 0x06, 0x03, 0xff, 0x04, 0x07, 0x00, 0xff, 0x0b, 0x0a, 0x00, 0xff, 0x0d, 0x0f, 0x10, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x0e, 0x0d, 0x0f, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x10, 0x0d, 0x0f, 0xff, 0x0e, 0x0f, 0x0d, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x0d, 0x0d, 0x0d, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x0d, 0x0d, 0x0d, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0x83, 0x83, 0x83, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x1e, 0x1c, 0x1b, 0xff, 0xbe, 0xc0, 0xc0, 0xff, 0xff, 0xfe, 0xfd, 0xff, 0xd0, 0xd3, 0xd7, 0xff, 0xbb, 0xbf, 0xc0, 0xff, 0xca, 0xc5, 0xc7, 0xff, 0xbf, 0xc4, 0xc3, 0xff, 0xc1, 0xc3, 0xc4, 0xff, 0xc3, 0xc2, 0xc4, 0xff, 0xc3, 0xc4, 0xc2, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 0xc1, 0xc0, 0xc2, 0xff, 0xc1, 0xc2, 0xc0, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 0xc4, 0xc4, 0xc4, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbe, 0xbe, 0xbe, 0xff, 0xec, 0xec, 0xec, 0xff, 0xff, 0xff, 0xff, 0xff, 0x67, 0x67, 0x67, 0xff, 0x02, 0x02, 0x02, 0xff, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0x37, 0x39, 0x3a, 0xff, 0xd0, 0xd3, 0xd1, 0xff, 0xfd, 0xff, 0xfc, 0xff, 0xfe, 0xfd, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x0b, 0x0b, 0x0b, 0xff, 0x02, 0x02, 0x02, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x02, 0x04, 0x05, 0xff, 0x15, 0x18, 0x16, 0xff, 0x1b, 0x1c, 0x18, 0xff, 0x14, 0x19, 0x1a, 0xff, 0x19, 0x19, 0x19, 0xff, 0x1f, 0x19, 0x1e, 0xff, 0x1a, 0x19, 0x1d, 0xff, 0x19, 0x1c, 0x1a, 0xff, 0x1a, 0x1b, 0x19, 0xff, 0x1d, 0x1b, 0x1b, 0xff, 0x1b, 0x1a, 0x1e, 0xff, 0x19, 0x1a, 0x18, 0xff, 0x1d, 0x1b, 0x1b, 0xff, 0x1b, 0x1b, 0x1b, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0xff, 
#endif
};

const lv_img_dsc_t battery_01 = {
  .header.always_zero = 0,
  .header.w = 27,
  .header.h = 14,
  .data_size = 378 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = battery_01_map,
};

