/*
 * @Author: your name
 * @Date: 2021-10-10 20:52:23
 * @LastEditTime: 2021-10-15 22:59:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\pages.h
 */

#ifndef _PAGES_H_
#define _PAGES_H_

#include "BLE.h"
#include "lvgl.h"
#include "debug.h"
#include "statusBar.h"
#include "globalConfig.h"
#include "lv_port_edc.h"
#include "uiSource.h"
#include "navigation.h"

#define PAGES_NUM 3

struct PAGE{
    uint8_t index;

    lv_obj_t* cont;

    lv_obj_t* imgbtn;

    lv_obj_t* app;
} PAGE;

struct {
    uint8_t now_index;
    uint8_t last_index;

    lv_group_t* group;

    struct PAGE pages[PAGES_NUM];
} PAGES;

struct BLEAPP {
    lv_obj_t* cont;

    lv_obj_t* title_bar;

    lv_obj_t* label_title;
    
    lv_obj_t* img_back;

    lv_obj_t* spinner;

    lv_obj_t* list;

    lv_timer_t* timer;

    lv_group_t* group;

    uint8_t showNum;

} BLEAPP;

struct SWITCHAPP {
    lv_obj_t* cont;

    lv_obj_t* title_bar;

    lv_obj_t* label_title;
    
    lv_obj_t* img_back;

    lv_obj_t* img_on;

    lv_obj_t* img_off;

    lv_group_t* group;

    lv_timer_t* timer;
    
} SWITCHAPP;

struct
{
    struct BLEAPP bleapp;

    struct SWITCHAPP switchapp;

} APPS;

static lv_style_t style_btn;
static lv_style_t style_back;
static lv_style_t style_focused;

void Pages_Init();
static void Page_Next();
static void Page_Prev();
void Apps_Init(lv_obj_t* par);
void Page_Deload(bool is_next);
static void App_Enter(lv_obj_t* imgbtn);
static void Page_DeloadByimgbtn(lv_obj_t* imgbtn);
static void Bleapp_Update(lv_timer_t* timer);
static void Switch_Update(lv_timer_t* timer);
static lv_obj_t* Bleapp_Creater(lv_obj_t* par);
static lv_obj_t* Switchapp_Create(lv_obj_t* par);
static lv_obj_t* Msgbox_Create(lv_obj_t* par, const char* msg);


/**************************************************
 *                      PAGES
 * ***********************************************/
// 按键回调函数
static void imgbtn_check_cb(lv_event_t * event)
{
    App_Enter(lv_event_get_target(event));
}

static void imgbtn_focused_cb(lv_event_t * event)
{
    Page_DeloadByimgbtn(lv_event_get_target(event));
}

static void Page_Create(struct PAGE* page, uint8_t index, const lv_img_dsc_t* img){

    lv_obj_t* cont = lv_obj_create(NULL);
    lv_obj_set_size(cont, 128, 128);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_PART_MAIN);

    lv_obj_t *imgbtn = lv_imgbtn_create(cont);
    lv_obj_center(imgbtn);
    lv_obj_set_width(imgbtn, 64);
    // lv_obj_add_style(imgbtn, &style_def, 0);
    // lv_obj_add_style(imgbtn, &style_pr, LV_STATE_PRESSED);
    lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, img, NULL);
    lv_obj_add_event_cb(imgbtn, imgbtn_check_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(imgbtn, imgbtn_focused_cb, LV_EVENT_FOCUSED, NULL);
    lv_group_t *group = Get_group(0);
    lv_group_add_obj(group, imgbtn);

    page->index = index;
    page->cont = cont;
    page->imgbtn = imgbtn;
}


void Pages_Init(){
    const lv_img_dsc_t* img;
    for (int i=0; i<PAGES_NUM; i++){
        switch (i){
            case 0: img = &ble_ico;break;
            case 1: img = &switch_ico;break;
            case 2: img = &setting_ico;break;
        }
        Page_Create(&PAGES.pages[i], i, img);
    }

    // 列表按键样式
    lv_style_init(&style_btn);
    lv_style_set_text_color(&style_btn, lv_color_white());
    lv_style_set_bg_color(&style_btn, lv_color_black());

    lv_style_init(&style_focused);
    lv_style_set_shadow_width(&style_focused, 5);
    lv_style_set_shadow_spread(&style_focused, 2);
    lv_style_set_shadow_color(&style_focused, lv_color_make(155, 155, 155));
    // 返回键样式
    lv_style_init(&style_back);
    lv_style_set_shadow_width(&style_back, 2);
    lv_style_set_shadow_spread(&style_back, 2);
    lv_style_set_shadow_color(&style_back, lv_color_make(63, 63, 63));

    PAGES.group = Get_group(0);
    PAGES.now_index = PAGES.last_index = 0;
}

// void my_timer(lv_timer_t * timer){
//     Page_Next();
// }
void Page_Deload(bool is_next){
    if (PAGES.now_index != PAGES.last_index) {
        if (is_next)
            lv_scr_load_anim(PAGES.pages[PAGES.now_index].cont, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
        else
            lv_scr_load_anim(PAGES.pages[PAGES.now_index].cont, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
    }
    else
    {
        lv_scr_load_anim(PAGES.pages[PAGES.now_index].cont, LV_SCR_LOAD_ANIM_MOVE_TOP, 1000, 0, false);
        lv_indev_set_group(Get_indev(), PAGES.group);
        lv_group_focus_obj(PAGES.pages[PAGES.now_index].imgbtn);
    }
    PAGES.last_index = PAGES.now_index;

    // lv_timer_t * timer = lv_timer_create(my_timer, 3000, NULL);
    // lv_timer_set_repeat_count(timer, 1);
}

static void Page_Next(){
    PAGES.now_index = (PAGES.now_index+1) % 3;
    Page_Deload(true);
}

static void Page_Prev(){
    PAGES.now_index = PAGES.now_index==0?2:PAGES.now_index-1;
    Page_Deload(false);
}

static void Page_DeloadByimgbtn(lv_obj_t* imgbtn){
    for (int i=0; i<PAGES_NUM; i++) {
        if (PAGES.pages[i].imgbtn == imgbtn && i != PAGES.now_index) {
            if ((i - PAGES.now_index > 0 && i - PAGES.now_index <= 1) || (i - PAGES.now_index == -2))
            {
                Page_Next();
                break;
            }
            else
            {
                Page_Prev();
                break;
            }
        }
    }
}

static void App_Enter(lv_obj_t* imgbtn){
    Navigation_Appear(false);   //箭头消失
    StatusBar_Appear(false);    //状态栏消失
    for (int i=0; i<PAGES_NUM; i++) {
        if (PAGES.pages[i].imgbtn == imgbtn) {
            switch (i){
                case 0:
                    Bleapp_Creater(NULL);
                    lv_scr_load_anim(APPS.bleapp.cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1500, false);
                    lv_timer_resume(APPS.bleapp.timer);
                    lv_indev_set_group(Get_indev(), APPS.bleapp.group);
                    lv_group_focus_obj(APPS.bleapp.img_back);
                    startScan();
                    break;
                case 1:
                    Switchapp_Create(NULL);
                    lv_scr_load_anim(APPS.switchapp.cont, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1500, false);
                    lv_timer_resume(APPS.switchapp.timer);
                    lv_indev_set_group(Get_indev(), APPS.switchapp.group);
                    lv_group_focus_obj(APPS.switchapp.img_back);
                    break;
            }
            return;
        }
    }
}



/**************************************************
 *                      APP
 * ***********************************************/
static void ble_back_event_cb(lv_event_t * event)
{
    stopScan();
    clearScan();
    APPS.bleapp.showNum = 0;
    lv_timer_pause(APPS.bleapp.timer);
    Page_Deload(NULL);
    StatusBar_Appear(true);
    Navigation_Appear(true);
    lv_timer_del(APPS.bleapp.timer);
}

static void switch_back_event_cb(lv_event_t * event)
{
    lv_timer_pause(APPS.switchapp.timer);
    Page_Deload(NULL);
    StatusBar_Appear(true);
    Navigation_Appear(true);
    lv_timer_del(APPS.switchapp.timer);
}

static void connectBle_event_cb(lv_event_t * event){
    uint32_t index =  lv_obj_get_child_id(lv_group_get_focused(APPS.bleapp.group));
    stopScan();
    if (connectToServer(&bleServer.addresses[index])){
        Msgbox_Create(lv_layer_top(), "连接成功!");
    }
    else {
        Msgbox_Create(lv_layer_top(), "连接失败!");
    }
}

static void msgbox_close_click_event_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * mbox = lv_obj_get_parent(btn);
    lv_indev_set_group(Get_indev(), Get_group(1));

    if(lv_obj_has_flag(mbox, LV_OBJ_FLAG_WIDGET_1)) lv_obj_del(lv_obj_get_parent(mbox));
    else lv_obj_del(mbox);
}

static lv_obj_t* Msgbox_Create(lv_obj_t* par, const char* msg){
    static const char * btns[] ={""};
    lv_obj_t* mbox = lv_msgbox_create(lv_scr_act(), "消息", msg, btns, true);
    lv_obj_center(mbox);
    lv_obj_set_size(mbox, 90, 80);
    lv_obj_t* mbox_title = lv_msgbox_get_title(mbox);
    lv_obj_t* mbox_text = lv_msgbox_get_text(mbox);
    lv_obj_t* mbox_close_btn = lv_msgbox_get_close_btn(mbox);
    lv_obj_add_event_cb(mbox_close_btn, msgbox_close_click_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_text_font(mbox_title, &zh_cn_jheiti_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(mbox_text, &zh_cn_jheiti_12, LV_PART_MAIN);
    lv_group_add_obj(Get_group(3), mbox_close_btn);
    lv_indev_set_group(Get_indev(), Get_group(3));
    return mbox;
}

static void Bleapp_Update(lv_timer_t* timer)
{
    if(ble.doScan){
        lv_obj_clear_flag(APPS.bleapp.spinner, LV_OBJ_FLAG_HIDDEN);
    }
    else
        lv_obj_add_flag(APPS.bleapp.spinner, LV_OBJ_FLAG_HIDDEN);
    if(bleServer.bleServerNum != 0)
        if(APPS.bleapp.showNum != bleServer.bleServerNum){
            lv_obj_t* list_btn;
            for (int i=APPS.bleapp.showNum; i < bleServer.bleServerNum; i++){
                list_btn = lv_list_add_btn(APPS.bleapp.list, LV_SYMBOL_BLUETOOTH, bleServer.name[i].c_str());
                lv_obj_add_style(list_btn, &style_btn, LV_STATE_DEFAULT);
                lv_obj_add_style(list_btn, &style_focused, LV_STATE_FOCUSED);
                lv_obj_add_event_cb(list_btn, connectBle_event_cb, LV_EVENT_CLICKED, NULL);
                lv_group_add_obj(APPS.bleapp.group, list_btn);
            }
            APPS.bleapp.showNum = bleServer.bleServerNum;
        }
}

static void Switch_Update(lv_timer_t* timer)
{
    if(ble.switchStatus){
        lv_obj_clear_flag(APPS.switchapp.img_on, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(APPS.switchapp.img_off, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_obj_add_flag(APPS.switchapp.img_on, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(APPS.switchapp.img_off, LV_OBJ_FLAG_HIDDEN);
    }
}

static lv_obj_t* Bleapp_Creater(lv_obj_t* par){
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_t * title_bar = lv_obj_create(cont);
    lv_group_t* group = Get_group(1);
    // 背景黑色
    lv_obj_set_style_bg_color(cont, lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_remove_style_all(title_bar);
    lv_obj_set_style_bg_color(title_bar, lv_color_make(155, 155, 155),LV_PART_MAIN);
    lv_obj_set_style_bg_opa(title_bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(title_bar, 128, 20);
    lv_obj_set_align(title_bar, LV_ALIGN_TOP_MID);
    //返回图标
    lv_obj_t* img_back = lv_img_create(title_bar);
    lv_img_set_src(img_back, &back_ico);
    lv_obj_align(img_back, LV_ALIGN_LEFT_MID, 5, 0);
    lv_obj_add_style(img_back, &style_back,LV_STATE_FOCUSED);
    lv_obj_add_event_cb(img_back, ble_back_event_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, img_back);
    //标题
    lv_obj_t* label_title = lv_label_create(title_bar);
    lv_obj_set_align(label_title, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(label_title, &zh_cn_jkaiti_10, LV_PART_MAIN);
    lv_label_set_text(label_title, "蓝牙设备");
    //转转
    lv_obj_t * spinner = lv_spinner_create(title_bar, 1000, 60);
    lv_obj_set_size(spinner, 16, 16);
    lv_obj_align(spinner, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_set_style_arc_color(spinner, lv_color_make(155, 155, 155), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(spinner, 4, LV_PART_INDICATOR);
    // 列表
    lv_obj_t * list = lv_list_create(cont);
    lv_obj_set_size(list, 120, 100);
    lv_obj_set_style_bg_opa(list, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(list, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_align(list, LV_ALIGN_BOTTOM_MID);

    APPS.bleapp.cont = cont;
    APPS.bleapp.title_bar = title_bar;
    APPS.bleapp.img_back = img_back;
    APPS.bleapp.spinner = spinner;
    APPS.bleapp.list = list;
    APPS.bleapp.group = group;
    APPS.bleapp.showNum = 0;

    lv_timer_t* timer = lv_timer_create(Bleapp_Update, 1000, NULL);
    APPS.bleapp.timer = timer;
    lv_timer_pause(APPS.bleapp.timer);

    return APPS.bleapp.cont;
}

static lv_obj_t* Switchapp_Create(lv_obj_t* par) {
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_t * title_bar = lv_obj_create(cont);
    lv_group_t* group = Get_group(2);
    // 背景黑色
    lv_obj_set_style_bg_color(cont, lv_color_black(),LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN);
    // 状态栏灰色
    lv_obj_remove_style_all(title_bar);
    lv_obj_set_style_bg_color(title_bar, lv_color_make(155, 155, 155),LV_PART_MAIN);
    lv_obj_set_style_bg_opa(title_bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(title_bar, 128, 20);
    lv_obj_set_align(title_bar, LV_ALIGN_TOP_MID);
    //返回图标
    lv_obj_t* img_back = lv_img_create(title_bar);
    lv_img_set_src(img_back, &back_ico);
    lv_obj_align(img_back, LV_ALIGN_LEFT_MID, 5, 0);
    lv_obj_add_style(img_back, &style_back,LV_STATE_FOCUSED);
    lv_obj_add_event_cb(img_back, switch_back_event_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(group, img_back);
    //标题
    lv_obj_t* label_title = lv_label_create(title_bar);
    lv_obj_set_align(label_title, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(label_title, &zh_cn_jkaiti_10, LV_PART_MAIN);
    lv_label_set_text(label_title, "开关");
    //灯灭图片
    lv_obj_t *img_off = lv_img_create(cont);
    lv_obj_center(img_off);
    lv_obj_set_width(img_off, 64);
    lv_obj_align(img_off, LV_ALIGN_CENTER, 0, 10);
    lv_img_set_src(img_off, &deng_off);
    //灯亮图片
    lv_obj_t *img_on = lv_img_create(cont);
    lv_obj_center(img_on);
    lv_obj_set_width(img_on, 64);
    lv_obj_align(img_on, LV_ALIGN_CENTER, 0, 10);
    // lv_obj_add_flag(img_on, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(img_on, &deng_on);
    if (ble.switchStatus) 
        lv_obj_add_flag(img_off, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(img_on, LV_OBJ_FLAG_HIDDEN);

    APPS.switchapp.cont = cont;
    APPS.switchapp.img_back = img_back;
    APPS.switchapp.title_bar = title_bar;
    APPS.switchapp.img_on = img_on;
    APPS.switchapp.img_off = img_off;
    APPS.switchapp.group = group;

    lv_timer_t* timer = lv_timer_create(Switch_Update, 200, NULL);
    APPS.switchapp.timer = timer;
    lv_timer_pause(APPS.switchapp.timer);

    return APPS.switchapp.cont;
}

void Apps_Init(lv_obj_t* par){
    Bleapp_Creater(par);
    Switchapp_Create(par);
}

#endif