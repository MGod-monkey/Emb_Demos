// /*
//  * @Author: your name
//  * @Date: 2021-10-12 16:30:29
//  * @LastEditTime: 2021-10-14 16:05:59
//  * @LastEditors: Please set LastEditors
//  * @Description: In User Settings Edit
//  * @FilePath: \receiveClient_V8\include\ble_app.h
//  */

// #ifndef _APPS_H
// #define _APPS_H

// #include "BLE.h"
// #include "lvgl.h"
// #include "statusBar.h"
// #include "globalConfig.h"
// #include "lv_port_edc.h"
// #include "uiSource.h"
// #include "navigation.h"

// struct BLEAPP {
//     lv_obj_t* cont;

//     lv_obj_t* title_bar;

//     lv_obj_t* label_title;
    
//     lv_obj_t* img_back;

//     lv_obj_t* spinner;

//     lv_obj_t* list;

//     lv_timer_t* timer;

//     lv_group_t* group;

//     uint8_t showNum;

// } BLEAPP;

// struct SWITCHAPP {
//     lv_obj_t* cont;

//     lv_obj_t* title_bar;

//     lv_obj_t* label_title;
    
//     lv_obj_t* img_back;

//     lv_obj_t* img_on;

//     lv_obj_t* img_off;

//     lv_group_t* group;

//     lv_timer_t* timer;
    
// } SWITCHAPP;


// struct
// {
//     struct BLEAPP bleapp;

//     struct SWITCHAPP switchapp;

// } APPS;

// static lv_style_t style_btn;
// static lv_style_t style_focused;
// void Apps_Init(lv_obj_t* par);
// void APP_Deload(uint8_t index);
// static void Bleapp_Update(lv_timer_t* timer);
// // static void back_event_cb(lv_event_t * event);
// static lv_obj_t* Bleapp_Creater(lv_obj_t* par);
// static lv_obj_t* Switchapp_Create(lv_obj_t* par);

// static void Bleapp_Update(lv_timer_t* timer)
// {
    
//     if(ble.doScan)
//         lv_obj_clear_flag(APPS.bleapp.spinner, LV_OBJ_FLAG_HIDDEN);
//     else
//         lv_obj_add_flag(APPS.bleapp.spinner, LV_OBJ_FLAG_HIDDEN);
//     if(bleServer.bleServerNum != 0)
//         if(APPS.bleapp.showNum != bleServer.bleServerNum){
//             lv_obj_t* list_btn;
//             for (int i=APPS.bleapp.showNum; i < bleServer.bleServerNum; i++){
//                 list_btn = lv_list_add_btn(APPS.bleapp.list, LV_SYMBOL_BLUETOOTH, bleServer.name[i].c_str());
//                 lv_obj_add_style(list_btn, &style_btn, LV_STATE_DEFAULT);
//                 lv_obj_add_style(list_btn, &style_focused, LV_STATE_FOCUSED);
//                 lv_group_add_obj(APPS.bleapp.group, list_btn);
//                 // lv_obj_add_event_cb();
//             }
//             APPS.bleapp.showNum = bleServer.bleServerNum;
//         }
// }

// static lv_obj_t* Bleapp_Creater(lv_obj_t* par){
//     lv_obj_t * cont = lv_obj_create(NULL);
//     lv_obj_t * title_bar = lv_obj_create(cont);
//     lv_group_t* group = Get_group(1);
//     // 背景黑色
//     lv_obj_set_style_bg_color(cont, lv_color_black(),LV_PART_MAIN);
//     lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
//     lv_obj_remove_style_all(title_bar);
//     lv_obj_set_style_bg_color(title_bar, lv_color_make(155, 155, 155),LV_PART_MAIN);
//     lv_obj_set_style_bg_opa(title_bar, LV_OPA_COVER, LV_PART_MAIN);
//     lv_obj_set_size(title_bar, 128, 20);
//     lv_obj_set_align(title_bar, LV_ALIGN_TOP_MID);
//     //返回图标
//     lv_obj_t* img_back = lv_img_create(title_bar);
//     lv_img_set_src(img_back, &back_ico);
//     lv_obj_align(img_back, LV_ALIGN_LEFT_MID, 5, 0);
//     lv_group_add_obj(group, img_back);
//     lv_style_t style_back;
//     lv_style_init(&style_back);
//     lv_style_set_shadow_width(&style_back, 4);
//     lv_style_set_shadow_color(&style_back, lv_color_make(63, 63, 63));
//     lv_obj_add_style(img_back, &style_back,LV_STATE_FOCUSED);
//     //标题
//     lv_obj_t* label_title = lv_label_create(title_bar);
//     lv_obj_set_align(label_title, LV_ALIGN_CENTER);
//     lv_obj_set_style_text_font(label_title, &zh_cn_jkaiti_10, LV_PART_MAIN);
//     lv_label_set_text(label_title, "蓝牙设备");
//     //转转
//     lv_obj_t * spinner = lv_spinner_create(title_bar, 1000, 60);
//     lv_obj_set_size(spinner, 16, 16);
//     lv_obj_align(spinner, LV_ALIGN_RIGHT_MID, -5, 0);
//     lv_obj_set_style_arc_color(spinner, lv_color_make(155, 155, 155), LV_PART_INDICATOR);
//     lv_obj_set_style_arc_width(spinner, 4, LV_PART_INDICATOR);
//     // 列表
//     lv_obj_t * list = lv_list_create(cont);
//     lv_obj_set_size(list, 120, 100);
//     lv_obj_set_style_bg_opa(list, LV_OPA_COVER, LV_PART_MAIN);
//     lv_obj_set_style_bg_color(list, lv_color_black(), LV_PART_MAIN);
//     lv_obj_set_align(list, LV_ALIGN_BOTTOM_MID);
//     // 列表按键样式
//     lv_style_init(&style_btn);
//     lv_style_set_text_color(&style_btn, lv_color_white());
//     lv_style_set_bg_color(&style_btn, lv_color_black());

//     lv_style_init(&style_focused);
//     lv_style_set_shadow_width(&style_focused, 5);
//     lv_style_set_shadow_spread(&style_focused, 2);
//     lv_style_set_shadow_color(&style_focused, lv_color_make(155, 155, 155));

//     APPS.bleapp.cont = cont;
//     APPS.bleapp.title_bar = title_bar;
//     APPS.bleapp.img_back = img_back;
//     APPS.bleapp.spinner = spinner;
//     APPS.bleapp.list = list;
//     APPS.bleapp.group = group;
//     APPS.bleapp.showNum = 0;

//     lv_timer_t* timer = lv_timer_create(Bleapp_Update, 1000, NULL);
//     APPS.bleapp.timer = timer;
//     lv_timer_pause(APPS.bleapp.timer);
//     // lv_timer_pause(timer);

//     return APPS.bleapp.cont;
// }

// static lv_obj_t* Switchapp_Create(lv_obj_t* par) {
//     lv_obj_t * cont = lv_obj_create(NULL);
//     lv_obj_t * title_bar = lv_obj_create(cont);
//     lv_group_t* group = Get_group(2);
//     // 背景黑色
//     lv_obj_set_style_bg_color(cont, lv_color_black(),LV_PART_MAIN);
//     lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
//     // 状态栏灰色
//     lv_obj_remove_style_all(title_bar);
//     lv_obj_set_style_bg_color(title_bar, lv_color_make(155, 155, 155),LV_PART_MAIN);
//     lv_obj_set_style_bg_opa(title_bar, LV_OPA_COVER, LV_PART_MAIN);
//     lv_obj_set_size(title_bar, 128, 20);
//     lv_obj_set_align(title_bar, LV_ALIGN_TOP_MID);
//     //返回图标
//     lv_obj_t* img_back = lv_img_create(title_bar);
//     lv_img_set_src(img_back, &back_ico);
//     lv_obj_align(img_back, LV_ALIGN_LEFT_MID, 5, 0);
//     lv_group_add_obj(group, img_back);
//     //标题
//     lv_obj_t* label_title = lv_label_create(title_bar);
//     lv_obj_set_align(label_title, LV_ALIGN_CENTER);
//     lv_obj_set_style_text_font(label_title, &zh_cn_jkaiti_10, LV_PART_MAIN);
//     lv_label_set_text(label_title, "开关");
//     //灯灭图片
//     lv_obj_t *img_off = lv_img_create(cont);
//     lv_obj_center(img_off);
//     lv_obj_set_width(img_off, 64);
//     lv_obj_align(img_off, LV_ALIGN_CENTER, 0, 10);
//     // lv_obj_add_style(imgbtn, &style_def, 0);
//     // lv_obj_add_style(imgbtn, &style_pr, LV_STATE_PRESSED);
//     lv_img_set_src(img_off, &deng_off);
//     //灯亮图片
//     lv_obj_t *img_on = lv_img_create(cont);
//     lv_obj_center(img_on);
//     lv_obj_set_width(img_on, 64);
//     lv_obj_align(img_on, LV_ALIGN_CENTER, 0, 10);
//     lv_obj_add_flag(img_on, LV_OBJ_FLAG_HIDDEN);
//     // lv_obj_add_style(imgbtn, &style_def, 0);
//     // lv_obj_add_style(imgbtn, &style_pr, LV_STATE_PRESSED);
//     lv_img_set_src(img_on, &deng_on);

//     APPS.switchapp.cont = cont;
//     APPS.switchapp.img_back = img_back;
//     APPS.switchapp.title_bar = title_bar;
//     APPS.switchapp.img_on = img_on;
//     APPS.switchapp.img_off = img_off;
//     APPS.switchapp.group = group;

//     return APPS.switchapp.cont;
// }

// void Apps_Init(lv_obj_t* par){
//     Bleapp_Creater(par);
//     Switchapp_Create(par);
// }

// void APP_Deload(uint8_t index){
//     switch (index){
//         case 0:
//             lv_scr_load_anim(APPS.bleapp.cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1500, false);
//             lv_timer_resume(APPS.bleapp.timer);
//             lv_indev_set_group(Get_indev(), APPS.bleapp.group);
//             lv_group_focus_obj(APPS.bleapp.img_back);
//             startScan();
//             return;
//         case 1:
//             lv_scr_load_anim(APPS.switchapp.cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1500, false);
//             lv_indev_set_group(Get_indev(), APPS.switchapp.group);
//             lv_group_focus_obj(APPS.switchapp.img_back);
//             return;
//     }
// }

// #endif // !_BLE_APP_H


