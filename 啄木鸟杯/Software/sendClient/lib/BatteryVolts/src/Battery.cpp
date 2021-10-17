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
#include "Arduino.h"
#include "Battery.h"

Battery::Battery(int addressPin, float convFactor, int reads)
{
    _reads = reads;
    _convFactor = convFactor;
    _addressPin = addressPin;
    // _initVoltsArray();
}

Battery::Battery(int addressPin, float convFactor)
{
    _reads = DEF_READS;
    _convFactor = convFactor;
    _addressPin = addressPin;
    // _initVoltsArray();
}

Battery::Battery(int addressPin)
{
    _reads = DEF_READS;
    _convFactor = DEF_CONV_FACTOR;
    _addressPin = addressPin;
    // _initVoltsArray();
}

Battery::Battery()
{
    _reads = DEF_READS;
    _convFactor = DEF_CONV_FACTOR;
    _addressPin = DEF_PIN;
    // _initVoltsArray();
}

int Battery::getAnalogPin()
{
    return _addressPin;
}
float Battery::getConvFactor()
{
    return _convFactor;
}
    
/**
 * Loads each voltage value in its matching charge element (index)
 */
// void Battery::_initVoltsArray(){
//     _vs[0] = 3200; 
//     _vs[1] = 3250; _vs[2] = 3300; _vs[3] = 3350; _vs[4] = 3400; _vs[5] = 3450;
//     _vs[6] = 3500; _vs[7] = 3550; _vs[8] = 3600; _vs[9] = 3650; _vs[10] = 3700;
//     _vs[11] = 3703; _vs[12] = 3706; _vs[13] = 3710; _vs[14] = 3713; _vs[15] = 3716;
//     _vs[16] = 3719; _vs[17] = 3723; _vs[18] = 3726; _vs[19] = 3729; _vs[20] = 3732;
//     _vs[21] = 3735; _vs[22] = 3739; _vs[23] = 3742; _vs[24] = 3745; _vs[25] = 3748;
//     _vs[26] = 3752; _vs[27] = 3755; _vs[28] = 3758; _vs[29] = 3761; _vs[30] = 3765;
//     _vs[31] = 3768; _vs[32] = 3771; _vs[33] = 3774; _vs[34] = 3777; _vs[35] = 3781;
//     _vs[36] = 3784; _vs[37] = 3787; _vs[38] = 3790; _vs[39] = 3794; _vs[40] = 3797;
//     _vs[41] = 3800; _vs[42] = 3805; _vs[43] = 3811; _vs[44] = 3816; _vs[45] = 3821;
//     _vs[46] = 3826; _vs[47] = 3832; _vs[48] = 3837; _vs[49] = 3842; _vs[50] = 3847;
//     _vs[51] = 3853; _vs[52] = 3858; _vs[53] = 3863; _vs[54] = 3868; _vs[55] = 3874;
//     _vs[56] = 3879; _vs[57] = 3884; _vs[58] = 3889; _vs[59] = 3895; _vs[60] = 3900;
//     _vs[61] = 3906; _vs[62] = 3911; _vs[63] = 3917; _vs[64] = 3922; _vs[65] = 3928;
//     _vs[66] = 3933; _vs[67] = 3939; _vs[68] = 3944; _vs[69] = 3950; _vs[70] = 3956;
//     _vs[71] = 3961; _vs[72] = 3967; _vs[73] = 3972; _vs[74] = 3978; _vs[75] = 3983;
//     _vs[76] = 3989; _vs[77] = 3994; _vs[78] = 4000; _vs[79] = 4008; _vs[80] = 4015;
//     _vs[81] = 4023; _vs[82] = 4031; _vs[83] = 4038; _vs[84] = 4046; _vs[85] = 4054;
//     _vs[86] = 4062; _vs[87] = 4069; _vs[88] = 4077; _vs[89] = 4085; _vs[90] = 4092;
//     _vs[91] = 4100; _vs[92] = 4111; _vs[93] = 4122; _vs[94] = 4133; _vs[95] = 4144;
//     _vs[96] = 4156; _vs[97] = 4167; _vs[98] = 4178; _vs[99] = 4189; _vs[100] = 4200;
// }

int Battery::getBatteryChargeLevel()
{
    int readValue = _analogRead(_addressPin);
    double volts = _analogReadToVolts(readValue);
    int chargeLevel = _getChargeLevel(volts);
    return chargeLevel;
}

int Battery::pinRead(){
    return _analogRead(_addressPin); 
}

int Battery::_analogRead(int pinNumber){
    int totalValue = 0;
    int averageValue = 0;
    for(int i = 0; i < _reads; i++){
       totalValue += analogRead(pinNumber);
    }
    averageValue = totalValue / _reads;
    return averageValue; 
}
/**
 * Performs a binary search to find the index corresponding to a voltage.
 * The index of the array is the charge %
*/
int Battery::_getChargeLevel(int volts){
  // int idx = 50;
  // int prev = 0;
  // int half = 0;
  if (volts >= 4210)
    return -1;
  if (volts <= 3200)
    return 0;
  return (volts - 3200) / 10;


  // while(true){
  //   half = abs(idx - prev) / 2;
  //   prev = idx;
  //   if(volts >= _vs[idx]){
  //     idx = idx + half;
  //   }else{
  //     idx = idx - half;
  //   }
  //   if (prev == idx){
  //     break;
  //   }
  // }
  // return idx;
}

int Battery::_analogReadToVolts(int readValue){
  int volts; 
  volts = (int)(readValue * _convFactor);
  return volts;
}

int Battery::getBatteryVolts(){
    int readValue = analogRead(_addressPin);
    return _analogReadToVolts(readValue);
}
