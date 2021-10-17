/*
 * @Author: your name
 * @Date: 2021-10-05 17:59:45
 * @LastEditTime: 2021-10-14 22:14:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\lv_port_edc.h
 */

#ifndef _LV_PORT_EDC_H
#define _LV_PORT_EDC_H

#include "lvgl.h"
#include "RotaryEnc.h"


static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
lv_indev_t * Get_indev(void);
lv_group_t * Get_group(uint8_t index);
// static void encoder_handler(void);

/**********************
 *  STATIC VARIABLES
 **********************/
// static int32_t encoder_diff;
// static lv_indev_state_t encoder_state;

static lv_indev_t *indev_encoder;
static lv_group_t *group_1;
static lv_group_t *group_2;
static lv_group_t *group_3;
static lv_group_t *group_4;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);
    group_1 = lv_group_create();
    group_2 = lv_group_create();
    group_3 = lv_group_create();
    group_4 = lv_group_create();
    lv_indev_set_group(indev_encoder, group_1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Encoder
 * -----------------*/

/*初识化编码器*/
static void encoder_init(void)
{
    REncoder_Init();
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;
    uint8_t act_enc = ENC_Scan(0);

    if(act_enc != 0) {
        switch(act_enc) {
            case 1:
                act_enc = LV_KEY_ENTER;
                data->state = LV_INDEV_STATE_PRESSED;	
                break;
            case 2:
                act_enc = LV_KEY_RIGHT;
                data->state = LV_INDEV_STATE_RELEASED;
                data->enc_diff = 1;
                break;
            case 3:
                act_enc = LV_KEY_LEFT;
                data->state = LV_INDEV_STATE_RELEASED;
                data->enc_diff = -1;
                break;
        }
        last_key = (uint32_t)act_enc;
    }
    data->key = last_key;
}

// /*Call this function in an interrupt to process encoder events (turn, press)*/
// static void encoder_handler(void)
// {
//     /*Your code comes here*/

//     encoder_diff += 0;
//     encoder_state = LV_INDEV_STATE_REL;
// }

lv_indev_t * Get_indev(void)
{
    return indev_encoder;
}
lv_group_t *Get_group(uint8_t index)
{
    switch (index){
        case 0: return group_1;
        case 1: return group_2;
        case 2: return group_3;
        case 3: return group_4;
    }
    return group_1;
}

#endif
