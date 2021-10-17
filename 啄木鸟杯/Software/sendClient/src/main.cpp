#include <Arduino.h>
#include <NimBLEDevice.h>
#include <esp_sleep.h>
#include <Battery.h>


#define BATT_Pin    34
#define Switch_Pin  22
#define Wakeup_Pin  32
#define LED_Pin     23
#define convFactor  1.7
#define reads       20
#define timeout     10000

static NimBLEServer* pServer;
static NimBLEService* pBATTService;
static NimBLEService* pSwitchService;
int switch_status = 0;
int switch_status_last = 0;
char* switch_str = "off";
int batteryLevel = 0;
static unsigned long timer = 0;
static NimBLEAdvertising* pAdvertising;
static Battery* BL = new Battery(BATT_Pin, (float)convFactor, reads);

/**                   LED事件                 */
void openOrColoseLED(uint8_t val){
    digitalWrite(LED_Pin, val);
}

void flashLED(uint8_t period=500, int count=1){
    for (int i=0; i < count; i++){
        openOrColoseLED(LOW);
        delay(period);
        openOrColoseLED(HIGH);
        delay(period);
    }
}

/**              服务器连接回调函数                   */  
class ServerCallbacks: public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        Serial.println("Client connected");
        Serial.println("Multi-connect support: start advertising");
        openOrColoseLED(HIGH);
        NimBLEDevice::startAdvertising();
    };

    void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) {
        Serial.print("Client address: ");
        Serial.println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
        /** We can use the connection handle here to ask for different connection parameters.
         *  Args: connection handle, min connection interval, max connection interval
         *  latency, supervision timeout.
         *  Units; Min/Max Intervals: 1.25 millisecond increments.
         *  Latency: number of intervals allowed to skip.
         *  Timeout: 10 millisecond increments, try for 5x interval time for best results.  
         */
        openOrColoseLED(HIGH);
        pServer->updateConnParams(desc->conn_handle, 24, 48, 0, 60);
    };
    void onDisconnect(NimBLEServer* pServer) {
        Serial.println("Client disconnected - start advertising");
        openOrColoseLED(LOW);
        timer = millis();
        // NimBLEDevice::startAdvertising();
    };
    void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
        Serial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
    };
};

/**                     特征动作的处理程序类                     */
class CharacteristicCallbacks: public NimBLECharacteristicCallbacks {
    void onRead(NimBLECharacteristic* pCharacteristic){
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.print(": onRead(), value: ");
        Serial.println(pCharacteristic->getValue().c_str());
    };

    void onWrite(NimBLECharacteristic* pCharacteristic) {
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.print(": onWrite(), value: ");
        Serial.println(pCharacteristic->getValue().c_str());
        flashLED(300, 2);
    };
    /** Called before notification or indication is sent, 
     *  the value can be changed here before sending if desired.
     */
    void onNotify(NimBLECharacteristic* pCharacteristic) {
        Serial.println("Sending notification to clients");
    };


    /** The status returned in status is defined in NimBLECharacteristic.h.
     *  The value returned in code is the NimBLE host return code.
     */
    void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) {
        String str = ("Notification/Indication status code: ");
        str += status;
        str += ", return code: ";
        str += code;
        str += ", "; 
        str += NimBLEUtils::returnCodeToString(code);
        Serial.println(str);
    };

    void onSubscribe(NimBLECharacteristic* pCharacteristic, ble_gap_conn_desc* desc, uint16_t subValue) {
        String str = "Client ID: ";
        str += desc->conn_handle;
        str += " Address: ";
        str += std::string(NimBLEAddress(desc->peer_ota_addr)).c_str();
        if(subValue == 0) {
            str += " Unsubscribed to ";
        }else if(subValue == 1) {
            str += " Subscribed to notfications for ";
        } else if(subValue == 2) {
            str += " Subscribed to indications for ";
        } else if(subValue == 3) {
            str += " Subscribed to notifications and indications for ";
        }
        str += std::string(pCharacteristic->getUUID()).c_str();

        Serial.println(str);
        flashLED();
    };
};
    
/**                   描述符操作的处理程序类               */    
class DescriptorCallbacks : public NimBLEDescriptorCallbacks {
    void onWrite(NimBLEDescriptor* pDescriptor) {
        std::string dscVal((char*)pDescriptor->getValue(), pDescriptor->getLength());
        Serial.print("Descriptor witten value:");
        Serial.println(dscVal.c_str());
    };

    void onRead(NimBLEDescriptor* pDescriptor) {
        Serial.print(pDescriptor->getUUID().toString().c_str());
        Serial.println("Descriptor read");
    };
};


/** Define callback instances globally to use for multiple Charateristics \ Descriptors */ 
static DescriptorCallbacks dscCallbacks;
static CharacteristicCallbacks chrCallbacks;


void bleInit(){
    Serial.println("Starting NimBLE Server");

    /** sets device name */
    NimBLEDevice::init("ESP32_SClient");

    /** Optional: set the transmit power, default is 3db */
    NimBLEDevice::setPower(ESP_PWR_LVL_P9); /** +9db */

    //NimBLEDevice::setSecurityAuth(false, false, true); 
    NimBLEDevice::setSecurityAuth(/*BLE_SM_PAIR_AUTHREQ_BOND*/BLE_SM_PAIR_AUTHREQ_MITM | BLE_SM_PAIR_AUTHREQ_SC);

    pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
    pServer->advertiseOnDisconnect(true); // 设置客户端断开时自动广播
  
    pBATTService = pServer->createService("180F");    // 电池服务
    NimBLECharacteristic* pBATTLevelCharacteristic = pBATTService->createCharacteristic(   // 电池电量
                                                "2A19",
                                                NIMBLE_PROPERTY::READ |
                                                NIMBLE_PROPERTY::NOTIFY
                                              );
    NimBLECharacteristic* pBATTStatusCharacteristic = pBATTService->createCharacteristic(   // 电池电量状态
                                                "2A1A",
                                                NIMBLE_PROPERTY::READ |
                                                NIMBLE_PROPERTY::NOTIFY
                                              );
    pBATTLevelCharacteristic->setCallbacks(&chrCallbacks);
    pBATTStatusCharacteristic->setCallbacks(&chrCallbacks);
    pBATTStatusCharacteristic->setValue(0);

    NimBLE2904* pBATT2904 = (NimBLE2904*)pBATTLevelCharacteristic->createDescriptor("2904",NIMBLE_PROPERTY::READ,10);
    pBATT2904->setFormat(NimBLE2904::FORMAT_UTF8);
    pBATT2904->setValue("BATT");
    pBATT2904->setCallbacks(&dscCallbacks);

    pSwitchService = pServer->createService("FFF0");
    NimBLECharacteristic* pSwitchCharacteristic = pSwitchService->createCharacteristic(
                                               "FFF1",
                                               NIMBLE_PROPERTY::READ |
                                               NIMBLE_PROPERTY::WRITE|
                                               NIMBLE_PROPERTY::NOTIFY
                                              );

    pSwitchCharacteristic->setValue(switch_status);
    pSwitchCharacteristic->notify(true);
    pSwitchCharacteristic->setCallbacks(&chrCallbacks);

    /** Note a 0x2902 descriptor MUST NOT be created as NimBLE will create one automatically
     *  if notification or indication properties are assigned to a characteristic.
     */

    /** Custom descriptor: Arguments are UUID, Properties, max length in bytes of the value */
    NimBLEDescriptor* pSwitchdsc = pSwitchCharacteristic->createDescriptor(
                                               "2901",
                                               NIMBLE_PROPERTY::READ,
                                               20);
    pSwitchdsc->setValue("Switch");
    pSwitchdsc->setCallbacks(&dscCallbacks);

    /** Start the services when finished creating all Characteristics and Descriptors */  
    pBATTService->start();
    pSwitchService->start();

    pAdvertising = NimBLEDevice::getAdvertising();
    /** Add the services to the advertisment data **/
    pAdvertising->addServiceUUID(pBATTService->getUUID());
    pAdvertising->addServiceUUID(pSwitchService->getUUID());
    /** If your device is battery powered you may consider setting scan response
     *  to false as it will extend battery life at the expense of less data sent.
     */
    pAdvertising->setScanResponse(false);
    pAdvertising->start();

    Serial.println("Advertising Started");
}

/**  中断回调函数 */
/**   开关服务   */

ICACHE_RAM_ATTR void sendSwitch()
{
    detachInterrupt(digitalPinToInterrupt(Switch_Pin));
    switch_status = (switch_status + 1) % 2;
    attachInterrupt(digitalPinToInterrupt(Switch_Pin), sendSwitch, FALLING);
}

void setup() {
    Serial.begin(115200);
    // analogSetClockDiv(125);

    // 设置引脚
    pinMode(BATT_Pin, INPUT);
    pinMode(Switch_Pin, INPUT_PULLUP);
    pinMode(Wakeup_Pin, INPUT_PULLUP);
    pinMode(LED_Pin, OUTPUT);
    // 设置按键中断
    attachInterrupt(digitalPinToInterrupt(Switch_Pin), sendSwitch, FALLING);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)Wakeup_Pin, 0);
    // attachInterrupt(Wakeup_Pin, disconnectBLE, FALLING);
    // 初识化蓝牙服务
    bleInit();
}

void loop() {
    timer = millis();
    while (true){
        if(pServer->getConnectedCount()) {
            NimBLEService* pSvc = nullptr;
            NimBLECharacteristic* pChr = nullptr;

            pSvc = pServer->getServiceByUUID("180F");
            if(pSvc) {
                batteryLevel = BL->getBatteryChargeLevel();
                Serial.printf("battery level: %d\t", batteryLevel);
                Serial.printf("battery volts: %dmv\n", BL->getBatteryVolts());
                if (batteryLevel < 0) {
                    pChr = pSvc->getCharacteristic("2A1A");
                    if(pChr) {
                    pChr->setValue(1);
                    pChr->notify(true);
                    }
                } else {
                    pChr = nullptr;
                    pChr = pSvc->getCharacteristic("2A19");
                    if(pChr) {
                        pChr->setValue(batteryLevel);
                        pChr->notify(true);
                    }
                }
            }
            pSvc = nullptr;
            pChr = nullptr;

            if (switch_status != switch_status_last) {
                pSvc = pServer->getServiceByUUID("FFF0");
                if(pSvc) {
                    pChr = pSvc->getCharacteristic("FFF1");
                    if (pChr) {
                        pChr->setValue(switch_status); 
                        pChr->notify(true);
                    }
                }
                switch_status_last = switch_status;
            }
            delay(500);
        }
        else
        {
            if (millis() - timer >= timeout)
            {
                timer = millis();
                esp_deep_sleep_start(); //10s未操作进入睡眠模式
            }
            else
                flashLED();
        }   
    }
}