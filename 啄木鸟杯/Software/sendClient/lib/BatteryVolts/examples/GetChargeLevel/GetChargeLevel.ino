/*
 * @Author: your name
 * @Date: 2021-10-07 11:09:41
 * @LastEditTime: 2021-10-07 15:34:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_V8c:\Users\17814\Documents\PlatformIO\Projects\sendClient\lib\BatteryVolts\examples\GetChargeLevel\GetChargeLevel.ino
 */
#include <Battery.h>

//#define ADC_PIN 34
//#define CONV_FACTOR 1.7
//#define READS 20

Battery BL;
/**
 * If you need to change default values you can use it as
 * Battery BL(ADC_PIN, CONV_FACTOR, READS);
 */

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Value from pin: ");
  Serial.println(analogRead(34));
  Serial.print("Average value from pin: ");
  Serial.println(BL.pinRead());
  Serial.print("Volts: ");
  Serial.println(BL.getBatteryVolts());
  Serial.print("Charge level: ");
  Serial.println(BL.getBatteryChargeLevel());
  Serial.println("");
  delay(1000);
}
