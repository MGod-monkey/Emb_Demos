/*
 * @Author: your name
 * @Date: 2021-10-05 17:46:42
 * @LastEditTime: 2021-10-13 17:33:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8\include\ENC.h
 */
#ifndef _ROTARYENC_H_
#define _ROTARYENC_H_

#include "debug.h"
#include "globalConfig.h"
#include "MD_REncoder.h"
#include "MD_UISwitch.h"

#define ENC_NO_PRES	        0		//ENC_NO  
#define ENC_OK_PRES	        1		//ENC_OK  
#define ENC_NEXT_PRES	    2		//ENC_NEXT 
#define ENC_PREV_PRES		3		//ENC_PREV

static MD_REncoder R = MD_REncoder(RotaryPinA, RotaryPinB);		//旋转编码器
static MD_UISwitch_Digital S(ClickedPin, (uint8_t)LOW);
void REncoder_Init(void);		//旋转编码器初始化
uint8_t ENC_Scan(uint8_t mode); //旋转编码器扫描函数	

void REncoder_Init(void)
{
	R.begin();
	S.begin();
	S.enableDoublePress(false);
} 

uint8_t ENC_Scan(uint8_t mode)
{	
	MD_UISwitch::keyResult_t k = S.read();
	switch (k)
	{
		case MD_UISwitch::KEY_PRESS:     Serial.println("KEY_PRESS ");return ENC_OK_PRES; break; //now these clearly aren't the way to do it....
		case MD_UISwitch::KEY_LONGPRESS: Serial.println("KEY_LONG   "); break;
		case MD_UISwitch::KEY_RPTPRESS:  /*Serial.print("\nKEY_REPEAT ");*/ break;
		default:                         /*Serial.print("\nKEY_UNKNWN ");*/ break;
	}

	uint8_t x = R.read();
	if (x)
  	{
    	// x == DIR_CW;
		if (x == DIR_CW ) {
			serialPrintln("NEXT");              
			return ENC_NEXT_PRES;
		}
		else
		{
			serialPrintln("PREV");
			return ENC_PREV_PRES; //now these clearly aren't the way to do it....
		}
    }

	return ENC_NO_PRES;
}
#endif