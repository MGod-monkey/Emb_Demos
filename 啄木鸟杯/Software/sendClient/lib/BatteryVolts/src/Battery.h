/*
 * @Author: your name
 * @Date: 2021-10-07 11:09:41
 * @LastEditTime: 2021-10-12 12:41:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings E
 * @FilePath: \receiveClient_V8c:\Users\17814\Documents\PlatformIO\Projects\sendClient\lib\BatteryVolts\src\Battery.h
 */
/*
  MIT License
  
  Copyright (c) 2019 Pangodream
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/* 
 *  18650 Ion-Li battery charge
 */
  
#ifndef _Battery_H
#define _Battery_H

#include "Arduino.h"

#define DEF_PIN 34
#define DEF_CONV_FACTOR 1.7
#define DEF_READS 20

/*
 * 18650 Ion-Li battery charge
 * Calculates charge level of an 18650 Ion-Li battery
 */
class Battery {    
  public:  
    
    /*
    * Constructor
    * @param addressPin, ADC pin number where the voltage divider is connected to
    */
    Battery(int addressPin);
    
    /*
    * Constructor
    * @param addressPin, ADC pin number where the voltage divider is connected to
    * @param convFactor, Convertion factor for analog read units to volts
    */
    Battery(int addressPin, float convFactor);
    
    /*
    * Constructor
    * @param addressPin, ADC pin number where the voltage divider is connected to
    * @param convFactor, Convertion factor for analog read units to volts
    * @param reads, Number of reads of analog pin to calculate an average value
    */
    Battery(int addressPin, float convFactor, int reads);
    
    /*
    * Constructor
    */
    Battery();    

    /*
     * Get the battery charge level (0-100)
     * @return The calculated battery charge level
     */
    int getBatteryChargeLevel();
    int getBatteryVolts();
    int getAnalogPin();
    int pinRead();
    float getConvFactor();
       
  private:

    int    _addressPin;               //!< ADC pin used, default is GPIO34 - ADC1_6
    int    _reads;                    //Number of reads of ADC pin to calculate an average value
    float _convFactor;               //!< Convertion factor to translate analog units to volts
    // int _vs[101];                 //Array with voltage - charge definitions
    
    // void   _initVoltsArray();
    int    _getChargeLevel(int volts);
    int    _analogRead(int pinNumber);
    int _analogReadToVolts(int readValue);
    
};

#endif