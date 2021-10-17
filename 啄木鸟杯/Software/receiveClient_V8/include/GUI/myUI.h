/*
 * @Author: your name
 * @Date: 2021-09-16 22:07:54
 * @LastEditTime: 2021-10-15 21:05:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient\include\myUI\myUI.h
 */
#ifndef _MYUI_H_
#define _MYUI_H_

#include "lvgl.h"
#include "BLE.h"
#include "TFT_eSPI.h"
#include "uiSource.h"
#include "statusBar.h"
#include "pages.h"
#include "navigation.h"
#include "lv_port_edc.h"

                
TFT_eSPI tft = TFT_eSPI();
static void reconnectBLE(lv_timer_t* timer)
{
    loadBleServer();
}

static void deloadMainPage(lv_timer_t* timer)
{
    Page_Deload(NULL);
    // Apps_Init(NULL);
    // lv_obj_add_event_cb(APPS.bleapp.img_back, back_event_cb, LV_EVENT_CLICKED, NULL);
    StatusBar_Creater(lv_layer_top());
    Navigation_Creater(lv_layer_top());
    StatusBar_Appear(true);
    Navigation_Appear(true);
    lv_timer_t * _timer = lv_timer_create(reconnectBLE, 2000, NULL);
    lv_timer_set_repeat_count(_timer, 1);
}

//设置屏幕背景
// screen: 要改变的页面，mode: 模式选择
// 模式1：蓝色渐变
static void setBGColor(lv_obj_t *screen, uint8_t mode){
    switch(mode){
        case 0:
            lv_obj_set_style_bg_color(screen, lv_color_hex(30 * 256 * 256 + 164 * 256 + 254),LV_PART_MAIN);
            lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
            lv_obj_set_style_bg_grad_color(screen, lv_color_hex(161 * 256 * 256 + 253 * 256 + 204),LV_PART_MAIN);
            lv_obj_set_style_bg_main_stop(screen, 80, LV_PART_MAIN);
            lv_obj_set_style_bg_grad_stop(screen, 255, LV_PART_MAIN);
            lv_obj_set_style_bg_grad_dir(screen, LV_GRAD_DIR_VER, LV_PART_MAIN);
            break;
        // case 1:
        //     lv_obj_set_style_bg_color(screen, LV_COLOR_CYAN);
    }
}

class UI
{
    public:
        int16_t width, height;
        UI(uint16_t width, uint16_t height) : width(width), height(height){
            static lv_disp_draw_buf_t draw_buf;
            static lv_color_t buf[ TFT_WIDTH * 10 ];

            lv_init();
            tft.begin(); /* TFT 初识化 */
            tft.setRotation(TFT_ROTATION_R);
            lv_disp_draw_buf_init( &draw_buf, buf, NULL, TFT_WIDTH * 10 );

            /*初识化显示屏*/
            static lv_disp_drv_t disp_drv;
            lv_disp_drv_init( &disp_drv );
            disp_drv.hor_res = TFT_WIDTH;
            disp_drv.ver_res = TFT_HEIGHT;
            disp_drv.flush_cb = my_disp_flush;
            disp_drv.draw_buf = &draw_buf;
            lv_disp_drv_register( &disp_drv );
            lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

            lv_port_indev_init();	//输入设备接口初始化
        };
        /* 屏幕刷新 */
        static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
        {            
            uint32_t w = (area->x2 - area->x1 + 1);
            uint32_t h = (area->y2 - area->y1 + 1);
            
            tft.startWrite();
            tft.setAddrWindow(area->x1, area->y1, w, h);
            tft.pushColors(&color_p->full, w * h, true);
            tft.endWrite();

            lv_disp_flush_ready(disp);
        }
        void initUI(){
            lv_obj_t* screen_deload = lv_obj_create(NULL);
            lv_obj_t* logo_img = lv_img_create(screen_deload);
            lv_img_set_src(logo_img, &img_logo);
            lv_obj_align(logo_img, LV_ALIGN_TOP_MID, 0, 20);

            // 背景渐变色
            setBGColor(screen_deload, 0);

            // 欢迎文字
            lv_obj_t *label_welcome = lv_label_create(screen_deload);
            lv_obj_set_style_text_font(label_welcome, &zh_cn_jkaiti_14, LV_PART_MAIN);
            lv_obj_align(label_welcome, LV_ALIGN_CENTER, 0, 25);
            lv_label_set_text(label_welcome, "欢迎使用\n啄木鸟产品");
            lv_obj_set_style_text_align(label_welcome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

            lv_scr_load(screen_deload);

            Pages_Init();

            lv_timer_t * timer = lv_timer_create(deloadMainPage, 1000, NULL);
            lv_timer_set_repeat_count(timer, 1);
        }
        /* 翻转屏幕 */
        void setRotation(TFT_ROTATION_MODE mode){
            tft.setRotation(mode);
        }
};

#endif