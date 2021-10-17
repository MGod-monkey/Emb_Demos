/*
 * @Author: your name
 * @Date: 2021-09-23 11:37:08
 * @LastEditTime: 2021-10-15 17:00:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\src\main.cpp
 */

#include <lvgl.h>
#include <GUI/myUI.h>
#include <globalConfig.h>
#include <BLE.h>
UI *ui = new UI(TFT_WIDTH, TFT_HEIGHT);
int tip_count;

void setup()
{
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    #ifdef DEBUG_FLAG
        Serial.begin(115200);
    #endif
    bleInit();
    ui->initUI();
}

void loop()
{
    delay(5);
    lv_task_handler();
}