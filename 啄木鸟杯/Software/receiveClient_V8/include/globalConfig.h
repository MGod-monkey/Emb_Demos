/*
 * @Author: your name
 * @Date: 2021-09-19 17:21:44
 * @LastEditTime: 2021-10-15 21:14:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_lv7_11\include\globaConfig.h
 */

/* *********************  全局配置  ************************** */
#ifndef _GLOBALCONFIG_H_
#define _GLOBALCONFIG_H_

#define DEBUG_FLAG  //Debug标识

/**********************
 *     彩屏配置
 **********************/

#define TFT_WIDTH  128  //屏幕宽
#define TFT_HEIGHT 128  //屏幕高

//  #define TFT_RGB_ORDER TFT_RGB  // 颜色排序为RGB
#define TFT_RGB_ORDER TFT_BGR  // 颜色排序为BGR

// 引脚定义
#define TFT_MOSI 21 // SPI的MOSI引脚或叫SDA引脚
#define TFT_SCLK 22 // SPI的时钟引脚
#define TFT_CS   18 // SPI的片选引脚
#define TFT_DC   19 // SPI的指令控制引脚
#define TFT_RST  17 // 重置引脚
#define TFT_BL   23 // 背光引脚
//#define TFT_RST  -1  // 如果RST引脚接到3.3V上则设置为-1

#define TFT_ROTATION_MODE     uint8_t // 屏幕翻转方位，从排针朝上为上，上->下表示像素点从上到下
#define TFT_ROTATION_U        0   // 上->下
#define TFT_ROTATION_R        1   // 右->左
#define TFT_ROTATION_D        2   // 下->上
#define TFT_ROTATION_L        3   // 左->右

/**********************
 *     LVGL配置
 **********************/
// LV8.x已不支持该项目
// /* 水平和垂直方向支持的最大尺寸（非实际屏幕的尺寸，尽量不要设置过大，会消耗内存）.*/
// #define LV_HOR_RES_MAX          (128)
// #define LV_VER_RES_MAX          (128)
/*Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888)*/
#define LV_COLOR_DEPTH     16
#define LV_LVGL_H_INCLUDE_SIMPLE

/* 全局字体定义
 * 示例：
 * #define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE(my_font_1) \
 *                                LV_FONT_DECLARE(my_font_2)
 */
#define LV_FONT_CUSTOM_DECLARE

/**********************
 *     编码器配置
 **********************/
#define RotaryPinA 26
#define RotaryPinB 27
#define ClickedPin 25

/**********************
 *     蓝牙配置
 **********************/

#define DEFAULT_BLE_NAME "ESP_rClient"        // 默认蓝牙名称
#define MAX_SAVE_NUM         15              // 默认扫描保留的最大蓝牙数量
#define DEFAULT_SCANTIME     10              // 默认每次扫描时间（单位：s）
#define DEFAULT_INTERVAL_MS  100             // 默认扫描间隙（单位：ms）
#define DEFAULT_WINDOWS_MS   80             // 默认扫描窗口间隙（单位：ms）
#define DEFAULT_BLE_CONNECT_TIMEOUT 3       // 蓝牙连接超时时间（单位：s）

#endif