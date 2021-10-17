/*
 * @Author: your name
 * @Date: 2021-09-29 19:22:15
 * @LastEditTime: 2021-10-14 20:03:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MP3democ:\Users\17814\Documents\PlatformIO\Projects\receiveClient_V8\include\debug.h
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Arduino.h>
#include <globalConfig.h>

void serialPrint(const char c[]){
    #ifdef DEBUG_FLAG
        Serial.print(c);
    #endif
}

void serialPrint(const String &s){
    #ifdef DEBUG_FLAG
        Serial.print(s);
    #endif
}

void serialPrint(int num){
    #ifdef DEBUG_FLAG
        Serial.print(num);
    #endif
}

void serialPrint(uint8_t num){
    #ifdef DEBUG_FLAG
        Serial.print(num);
    #endif
}

void serialPrint(uint16_t num){
    #ifdef DEBUG_FLAG
        Serial.print(num);
    #endif
}

void serialPrint(uint32_t num){
    #ifdef DEBUG_FLAG
        Serial.print(num);
    #endif
}

void serialPrint(long num){
    #ifdef DEBUG_FLAG
        Serial.print(num);
    #endif
}

void serialPrintln(const char c[]){
    #ifdef DEBUG_FLAG
        Serial.println(c);
    #endif
}

void serialPrintln(const String &s){
    #ifdef DEBUG_FLAG
        Serial.println(s);
    #endif
}

void serialPrintln(int num){
    #ifdef DEBUG_FLAG
        Serial.println(num);
    #endif
}

void serialPrintln(uint8_t num){
    #ifdef DEBUG_FLAG
        Serial.println(num);
    #endif
}

void serialPrintln(uint16_t num){
    #ifdef DEBUG_FLAG
        Serial.println(num);
    #endif
}

void serialPrintln(uint32_t num){
    #ifdef DEBUG_FLAG
        Serial.println(num);
    #endif
}

void serialPrintln(long num){
    #ifdef DEBUG_FLAG
        Serial.println(num);
    #endif
}

#endif // !_DEBUG_H_