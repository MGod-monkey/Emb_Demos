/*
 * @Author: your name
 * @Date: 2021-10-09 17:57:25
 * @LastEditTime: 2021-10-15 15:54:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\clock.h
 */
#ifndef _CLOCK_H_
#define _CLOCK_H_
#include "stdint.h"

struct Clock_Info_t
{
    uint16_t year=0;
    uint8_t month=0;
    uint8_t day=0;
    uint8_t week=0;
    uint8_t hour=0;
    uint8_t minute=0;
    uint8_t second=0;
} clock_info_t;

void clockAddOneSeconde(){
    clock_info_t.second = (clock_info_t.second + 1) % 60;
    clock_info_t.minute = (clock_info_t.minute + (clock_info_t.second==0?1:0)) % 60;
    clock_info_t.hour = (clock_info_t.hour + (clock_info_t.minute==0?1:0)) % 60;
}

#endif // !_CLOCK_H_