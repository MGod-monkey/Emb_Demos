/*
 * @Author: your name
 * @Date: 2021-10-10 21:14:20
 * @LastEditTime: 2021-10-13 23:19:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\direction.h
 */

#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include "lvgl.h"
#include "uiSource.h"
#include "globalConfig.h"

#define NAVIGATION_LENGTH   12

struct
{
    lv_obj_t* cont;
    
    lv_obj_t* label_left;

    lv_obj_t* label_right;

    lv_obj_t* img_bottom;
} navigation;


/**           创建左右箭头及底部              */
lv_obj_t* Navigation_Creater(lv_obj_t* par){
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_style_bg_opa(cont, LV_OPA_0, LV_PART_MAIN);

    lv_obj_set_size(cont, TFT_WIDTH, TFT_HEIGHT);
    lv_obj_set_align(cont, LV_ALIGN_CENTER);

    navigation.cont = cont;

    // 底座
    lv_obj_t* img_bottom = lv_img_create(par);
    lv_img_set_src(img_bottom, &bottom);
    lv_obj_align(img_bottom, LV_ALIGN_BOTTOM_MID, 0, NAVIGATION_LENGTH);
    navigation.img_bottom = img_bottom;

    // 左右箭头
    lv_obj_t* label_left = lv_label_create(par);
    lv_label_set_text(label_left, LV_SYMBOL_LEFT);
    lv_obj_align(label_left, LV_ALIGN_LEFT_MID, -NAVIGATION_LENGTH, 0);
    lv_obj_set_style_text_color(label_left, lv_color_white(), 0);
    navigation.label_left = label_left;
    lv_obj_t* label_right = lv_label_create(par);
    lv_obj_align(label_right, LV_ALIGN_RIGHT_MID, NAVIGATION_LENGTH, 0);
    lv_label_set_text(label_right, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_color(label_right, lv_color_white(), 0);
    navigation.label_right = label_right;

    return navigation.cont;
}

void Navigation_Appear(bool en)
{
    int8_t start_left = -NAVIGATION_LENGTH;
    int8_t end_left = NAVIGATION_LENGTH;
    int8_t start_right = NAVIGATION_LENGTH;
    int8_t end_right = -NAVIGATION_LENGTH;
    int8_t start_bottom = NAVIGATION_LENGTH;
    int8_t end_bottom = -NAVIGATION_LENGTH;
    uint32_t delay_time = 1000;
    int8_t temp;
    if (!en)
    {
        temp = start_left;
        start_left = end_left;
        end_left = temp;

        temp = start_right;
        start_right = end_right;
        end_right = temp;

        temp = start_bottom;
        start_bottom = end_bottom;
        end_bottom = temp;

        delay_time = 0;
    }

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, navigation.label_left);
    lv_anim_set_values(&a1, start_left, end_left);
    lv_anim_set_time(&a1, 500);
    lv_anim_set_delay(&a1, delay_time);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a1, lv_anim_path_bounce);
    lv_anim_set_early_apply(&a1, true);
    lv_anim_start(&a1);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, navigation.label_right);
    lv_anim_set_values(&a2, start_right, end_right);
    lv_anim_set_time(&a2, 500);
    lv_anim_set_delay(&a2, delay_time);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a2, lv_anim_path_bounce);
    lv_anim_set_early_apply(&a2, true);
    lv_anim_start(&a2);

    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, navigation.img_bottom);
    lv_anim_set_values(&a3, start_bottom, end_bottom);
    lv_anim_set_time(&a3, 500);
    lv_anim_set_delay(&a3, delay_time);
    lv_anim_set_exec_cb(&a3, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a3, lv_anim_path_ease_out);
    lv_anim_set_early_apply(&a3, true);
    lv_anim_start(&a3);
}


#endif // !_NAVIGATION_H_
