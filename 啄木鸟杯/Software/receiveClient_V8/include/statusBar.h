#ifndef _STATUSBAR_H_
#define _STATUSBAR_H_

#include "lvgl.h"
#include "clock.h"
#include "BLE.h"
#include "uiSource.h"
#include "globalConfig.h"

#define STATUS_BAR_HEIGHT   20

struct
{
    lv_obj_t* cont;

    lv_timer_t* timer;

    lv_anim_t* anim;

    lv_obj_t* img_ble_on;

    lv_obj_t* img_ble_off;

    lv_obj_t* label_clock;

    lv_obj_t* img_battery_1;

    lv_obj_t* img_battery_2;
    
    lv_obj_t* img_battery_3;
    
    lv_obj_t* img_battery_4;
    
    lv_obj_t* img_battery_5;

    lv_obj_t * animimg_battery;
} statusBar;

static const lv_img_dsc_t* battery_charge_imgs[4] = {
	&battery_01,
	&battery_02,
	&battery_03,
	&battery_04,
};

static void StatusBar_Update(lv_timer_t* timer);

static void StatusBar_Update(lv_timer_t* timer)
{
    /* clock */
    clockAddOneSeconde();
    lv_label_set_text_fmt(statusBar.label_clock, "%02d:%02d", clock_info_t.minute, clock_info_t.second);
    /* ble */
    if (ble.connected) {
        lv_obj_add_flag(statusBar.img_ble_off, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(statusBar.img_ble_on, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_obj_clear_flag(statusBar.img_ble_off, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(statusBar.img_ble_on, LV_OBJ_FLAG_HIDDEN);
    }
    /* battery */
    if (ble.chargeStatus) {
        if (ble.showChargeImg){
            ble.showChargeImg = false;
            lv_obj_add_flag(statusBar.img_battery_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(statusBar.img_battery_5, LV_OBJ_FLAG_HIDDEN);
        }
        else {
            lv_obj_add_flag(statusBar.img_battery_5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        if (ble.batteryLevel >= 0 && ble.batteryLevel <= 25) {
            lv_obj_clear_flag(statusBar.img_battery_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
        }
        else if (ble.batteryLevel > 25 && ble.batteryLevel <= 50) {
            lv_obj_add_flag(statusBar.img_battery_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(statusBar.img_battery_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
        }
        else if (ble.batteryLevel > 50 && ble.batteryLevel <= 75) {
            lv_obj_add_flag(statusBar.img_battery_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(statusBar.img_battery_3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
        }
        else if (ble.batteryLevel > 75 && ble.batteryLevel <= 100) {
            lv_obj_add_flag(statusBar.img_battery_1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.img_battery_3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(statusBar.img_battery_4, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

/**           创建状态栏                */
lv_obj_t* StatusBar_Creater(lv_obj_t* par){
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);

    lv_obj_set_size(cont, TFT_WIDTH, STATUS_BAR_HEIGHT);
    lv_obj_set_y(cont, -STATUS_BAR_HEIGHT);

    statusBar.cont = cont;

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_text_font(&style, &zh_cn_jkaiti_14);

    /* ble */
    lv_obj_t* img_off = lv_img_create(cont);
    lv_img_set_src(img_off, &ble_disconnected);
    lv_obj_align(img_off, LV_ALIGN_LEFT_MID, 5, 0);
    statusBar.img_ble_off = img_off;

    lv_obj_t* img_on = lv_img_create(cont);
    lv_img_set_src(img_on, &ble_connected);
    lv_obj_align(img_on, LV_ALIGN_LEFT_MID, 5, 0);
    lv_obj_add_flag(img_on, LV_OBJ_FLAG_HIDDEN);
    statusBar.img_ble_on = img_on;

    /* clock */
    lv_obj_t* label = lv_label_create(cont);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "00:00");
    lv_obj_center(label);
    statusBar.label_clock = label;

    /* battery */
    lv_obj_t* img_1 = lv_img_create(cont);
    lv_img_set_src(img_1, &battery_01);
    lv_obj_align(img_1, LV_ALIGN_RIGHT_MID, -5, 0);
    statusBar.img_battery_1 = img_1;
    lv_obj_add_flag(img_1, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t* img_2 = lv_img_create(cont);
    lv_img_set_src(img_2, &battery_02);
    lv_obj_align(img_2, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_add_flag(img_2, LV_OBJ_FLAG_HIDDEN);
    statusBar.img_battery_2 = img_2;

    lv_obj_t* img_3 = lv_img_create(cont);
    lv_img_set_src(img_3, &battery_03);
    lv_obj_align(img_3, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_add_flag(img_3, LV_OBJ_FLAG_HIDDEN);
    statusBar.img_battery_3 = img_3;

    lv_obj_t* img_4 = lv_img_create(cont);
    lv_img_set_src(img_4, &battery_04);
    lv_obj_align(img_4, LV_ALIGN_RIGHT_MID, -5, 0);
    statusBar.img_battery_4 = img_4;

    lv_obj_t* img_5 = lv_img_create(cont);
    lv_img_set_src(img_5, &battery_05);
    lv_obj_align(img_5, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_add_flag(img_5, LV_OBJ_FLAG_HIDDEN);
    statusBar.img_battery_5 = img_5;

    lv_obj_t* animimg_battery = lv_animimg_create(cont);
    lv_obj_center(animimg_battery);
    lv_animimg_set_src(animimg_battery, (lv_img_dsc_t**)battery_charge_imgs, 4);
    lv_animimg_set_duration(animimg_battery, 1000);
    lv_animimg_set_repeat_count(animimg_battery, LV_ANIM_REPEAT_INFINITE);
    lv_obj_align(animimg_battery, LV_ALIGN_RIGHT_MID, -5, 0);

    statusBar.animimg_battery = animimg_battery;
    lv_obj_add_flag(statusBar.animimg_battery, LV_OBJ_FLAG_HIDDEN);
    lv_animimg_start(statusBar.animimg_battery);


    lv_timer_t* timer = lv_timer_create(StatusBar_Update, 1000, NULL);
    statusBar.timer = timer;

    return statusBar.cont;
}

void StatusBar_Appear(bool en)
{
    uint32_t start = -STATUS_BAR_HEIGHT;
    uint32_t end = 0;
    uint32_t delay_time = 1500;

    if (!en)
    {
        uint32_t temp = start;
        start = end;
        end = temp;
        delay_time = 500;
    }

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, statusBar.cont);
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, 500);
    lv_anim_set_delay(&a, delay_time);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_early_apply(&a, true);
    lv_anim_start(&a);
}


#endif // !_STATUSBAR_H_