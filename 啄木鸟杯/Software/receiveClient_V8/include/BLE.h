/*
 * @Author: your name
 * @Date: 2021-09-17 22:56:24
 * @LastEditTime: 2021-10-15 21:43:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient\include\BLE.h
 */

#ifndef _BLE_H_
#define _BLE_H_

#include <debug.h>
#include <EEPROM.h>
#include <bleUUID.h>
#include <NimBLEDevice.h>
#include <globalConfig.h>

static struct bleServer {
  uint8_t bleServerNum = 0;
  String name[MAX_SAVE_NUM];
  NimBLEAddress addresses[MAX_SAVE_NUM];
} bleServer;

static struct BLE {
    uint16_t intervalMSecs = DEFAULT_INTERVAL_MS;
    uint16_t windowMSecs = DEFAULT_WINDOWS_MS;
    uint32_t duration = DEFAULT_SCANTIME;
    bool doScan = false;
    bool connected = false;
    bool hadConnected = false;
    bool chargeStatus = false;
    bool showChargeImg = true;
    bool switchStatus = false;
    uint8_t batteryLevel = 100;
    NimBLEScan   * pScan;
    NimBLEAddress* pAdr;
    NimBLEClient * pClient;
} ble;

//******/
void bleInit();
void startScan();
void stopScan();
void restartScan();
void saveBleServer();
bool loadBleServer();
bool connectToServer(NimBLEAddress *pAdr);
bool reconnectToServer();
void setDuration(uint32_t duration);
void setWindowsMsecs(uint16_t windowMSecs);
void setTargeBLEDevice(NimBLEAddress *pAdr);
void setIntervalMsecs(uint16_t intervalMSecs);
static void scanEndedCB(NimBLEScanResults results);


// 客户端连接成功回调函数
class ClientCallbacks : public NimBLEClientCallbacks {
    void onConnect(NimBLEClient* pClient) {
        /** After connection we should change the parameters if we don't need fast response times.
         *  These settings are 150ms interval, 0 latency, 450ms timout.
         *  Timeout should be a multiple of the interval, minimum is 100ms.
         *  I find a multiple of 3-5 * the interval works best for quick response/reconnect.
         *  Min interval: 120 * 1.25ms = 150, Max interval: 120 * 1.25ms = 150, 0 latency, 60 * 10ms = 600ms timeout
         */
        serialPrintln("Connected!");
        ble.connected = true;
        pClient->updateConnParams(120,120,0,60);
    };

    void onDisconnect(NimBLEClient* pClient) {
        serialPrint(pClient->getPeerAddress().toString().c_str());
        serialPrintln("  disconnected! try reconnected once!");
        ble.connected = false;
        reconnectToServer();
    };
};

// 收到服务推送的数据时的回调函数
void notifyCB_BatteryLevel(NimBLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify){
    serialPrint("The Battery Charge Level: ");
    serialPrint(*pData);
    serialPrintln(" %");
    ble.batteryLevel = *pData;
    ble.chargeStatus = false;
    ble.showChargeImg = true;
}

void notifyCB_BatteryCharge(NimBLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify){
    serialPrint("The Battery Charge Status: ");
    serialPrint(*pData==1?"true":"false");
    ble.batteryLevel = *pData;
    ble.chargeStatus = true;
}

void notifyCB_Switch(NimBLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify){
    serialPrint("The Switch Status: ");
    serialPrintln(*pData==0?"off":"on");
    ble.switchStatus = *pData==0?false:true;
}

static ClientCallbacks clientCB;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
      if (advertisedDevice->haveName() && advertisedDevice->haveServiceUUID()) {
        std::string advmsg;
        advmsg += "Name: " + advertisedDevice->getName();
        advmsg += "\tAddress: " + advertisedDevice->getAddress().toString();
        advmsg += "\tserviceUUID: " + advertisedDevice->getServiceUUID().toString();
        serialPrintln(advmsg.c_str());
        if (advertisedDevice->haveName() && advertisedDevice->haveServiceUUID()){
            if (!addService(advertisedDevice->getName().c_str(), advertisedDevice->getAddress()))
                {
                    ble.pScan->stop();
                    ble.pScan->clearResults();
                    serialPrintln("The number of saved ble address has reached the max!");
                }
        }
      }
  };
  bool addService(const std::string servername, const NimBLEAddress address){
    if (++bleServer.bleServerNum >= MAX_SAVE_NUM) 
      return false;
    else {
      String name = servername.c_str();
      for (int i=0; i < bleServer.bleServerNum; i++){
        if (name == bleServer.name[i])  {bleServer.bleServerNum--;return true;}  //根据名称筛选重复蓝牙
      }
      bleServer.name[bleServer.bleServerNum-1] = servername.c_str();
      bleServer.addresses[bleServer.bleServerNum-1] = address;
    }
    return true;
  }
};

// 蓝牙初识化
void bleInit(){
    NimBLEDevice::init(DEFAULT_BLE_NAME);
    NimBLEDevice::setSecurityAuth(BLE_SM_PAIR_AUTHREQ_SC);
    // NimBLEDevice::setSecurityAuth(false, false, true);
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);
    ble.pScan = NimBLEDevice::getScan();
    ble.pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    ble.pScan->setActiveScan(true); //设置连续扫描
    ble.pScan->setInterval(ble.intervalMSecs);
    ble.pScan->setWindow(ble.windowMSecs);
    // pBLEScan->setFilterPolicy(BLE_HCI_SCAN_FILT_NO_WL);
    ble.pScan->clearResults();
    serialPrintln("BLE Client Inited!");
}

void scanEndedCB(NimBLEScanResults results){
    ble.doScan = false;
    serialPrint("Scan completed，scan count: ");
    serialPrint(String(results.getCount()).c_str());
    serialPrint("\tsaved：");
    serialPrintln(String(bleServer.bleServerNum).c_str());
    delay(100);
}

// 连接客户端
bool connectToServer(NimBLEAddress *pAdr) {
    ble.pClient = nullptr;
    setTargeBLEDevice(pAdr);
    
    if(!ble.pClient) {
        if(NimBLEDevice::getClientListSize() >= NIMBLE_MAX_CONNECTIONS) {
            serialPrintln("Max clients reached - no more connections available");
            ble.connected = false;
            return false;
        }

        ble.pClient = NimBLEDevice::createClient();

        serialPrintln("New client created");

        ble.pClient->setClientCallbacks(&clientCB, false);
        ble.pClient->setConnectionParams(12,12,0,51);
        ble.pClient->setConnectTimeout(DEFAULT_BLE_CONNECT_TIMEOUT);


        if (!ble.pClient->connect(*ble.pAdr)) {
            /** Created a client but failed to connect, don't need to keep it as it has no data */
            NimBLEDevice::deleteClient(ble.pClient);
            serialPrintln("Failed to connect, deleted client");
            ble.connected = false;
            return false;
        }
    }

    if(!ble.pClient->isConnected()) {
        if (!ble.pClient->connect(*ble.pAdr)) {
            serialPrintln("Failed to connect");
            ble.connected = false;
            return false;
        }
    }

    serialPrint("Connected to: ");
    serialPrint(ble.pClient->getPeerAddress().toString().c_str());
    serialPrint("\tRSSI: ");
    serialPrintln(ble.pClient->getRssi());

    NimBLERemoteService* pBATTSvc = nullptr;
    NimBLERemoteService* pSwitchSvc = nullptr;
    NimBLERemoteCharacteristic* pBATTLevelChr = nullptr;
    NimBLERemoteCharacteristic* pBATTStatusChr = nullptr;
    NimBLERemoteCharacteristic* pSwitchChr = nullptr;
    // NimBLERemoteDescriptor* pDsc = nullptr;
    pBATTSvc = ble.pClient->getService(Battery_Server);
    pBATTLevelChr = pBATTSvc->getCharacteristic(Battery_Level_Characteristic);
    pBATTStatusChr = pBATTSvc->getCharacteristic(Battery_Status_Characteristic);

    pSwitchSvc = ble.pClient->getService(Switch_Server);
    pSwitchChr = pSwitchSvc->getCharacteristic(Switch_Characteristic);
    // 电池电量服务
    if (pBATTLevelChr){
        if(pBATTLevelChr->canRead()){
            serialPrint("The Battery Charge Level: ");
            serialPrintln(pSwitchChr->readValue().c_str());
        }
        if(pBATTLevelChr->canNotify()) {
            //if(!pChr->registerForNotify(notifyCB)) {
            if(!pBATTLevelChr->subscribe(true, notifyCB_BatteryLevel)) {
                /** Disconnect if subscribe failed */
                ble.pClient->disconnect();
                ble.connected = false;
                return false;
            }
        }
    }
    // 充电状态服务
    if (pBATTStatusChr){
        if(pBATTStatusChr->canRead()){
            serialPrint("The Battery Charge Status: ");
            serialPrintln(pSwitchChr->readValue().c_str());
        }
        if(pBATTStatusChr->canNotify()) {
            //if(!pChr->registerForNotify(notifyCB)) {
            if(!pBATTStatusChr->subscribe(true, notifyCB_BatteryCharge)) {
                /** Disconnect if subscribe failed */
                ble.pClient->disconnect();
                ble.connected = false;
                return false;
            }
        }
    }
    // 开关状态服务
    if (pSwitchChr){
        if(pSwitchChr->canRead()){
            Serial.print("The Switch Status: ");
            serialPrintln(pSwitchChr->readValue().c_str());
        }
        if(pSwitchChr->canNotify()) {
            //if(!pChr->registerForNotify(notifyCB)) {
            if(!pSwitchChr->subscribe(true, notifyCB_Switch)) {
                /** Disconnect if subscribe failed */
                ble.pClient->disconnect();
                ble.connected = false;
                return false;
            }
        }
    }
    saveBleServer();
    ble.connected = true;
    return true;
}

// 重连蓝牙
bool reconnectToServer(){
    /** 检查是否能重连 **/
    ble.pClient = nullptr;
    if(NimBLEDevice::getClientListSize()) {
        ble.pClient = NimBLEDevice::getClientByPeerAddress(*ble.pAdr);
        if(ble.pClient){
            ble.pClient->setConnectTimeout(DEFAULT_BLE_CONNECT_TIMEOUT);
            if(!ble.pClient->connect(*ble.pAdr, false)) {
                serialPrintln("Reconnect failed");
                ble.connected = false;
                return false;
            }
            serialPrintln("Reconnected client");
            ble.connected = true;
            return true;
        }
        else {
            ble.pClient = NimBLEDevice::getDisconnectedClient();
            ble.connected = false;
            return false;
        }
    }
    ble.connected = false;
    return false;
}

// 掉电保存蓝牙服务器
void saveBleServer()
{
    EEPROM.begin(100);//向系统申请100kb ROM
    //开始写入
    String pAdrStr = ble.pAdr->toString().c_str();
    EEPROM.writeString(0, pAdrStr);
    EEPROM.commit();//执行写入ROM
    serialPrintln("Saved Ble Server To EEPROM!");
}
// 读取蓝牙服务器
bool loadBleServer()
{
    EEPROM.begin(100);
    char* pAdrStr=nullptr;
    pAdrStr = (char *)EEPROM.readString(0).c_str();
    if (pAdrStr != nullptr && pAdrStr[0] != '\0')
    {
        serialPrint("Read ble address: ");
        serialPrint(pAdrStr);
        serialPrintln("  ,try to connected");
        NimBLEAddress pAdr = NimBLEAddress(std::string(pAdrStr));
        ble.pAdr =  &pAdr;
        if (connectToServer(ble.pAdr)) return true;
        else return false;
    }
    else return false;
}

// 设置目标蓝牙
void setTargeBLEDevice(NimBLEAddress *pAdr){
    ble.pAdr = pAdr;
}
// 开始扫描
void startScan(){
    ble.doScan = true;
    ble.pScan->start(0, scanEndedCB);
}

// 停止扫描
void stopScan(){
    ble.doScan = false;
    ble.pScan->stop();
    ble.pScan->clearResults();
}

// 重新扫描
void restartScan(){
    // 清空存储的蓝牙数量
    memset(&bleServer, 0, sizeof(struct BLEServer));
    stopScan();
    startScan();
}
// 清除所有保存到的蓝牙设备
void clearScan(){
    memset(&bleServer, 0, sizeof(struct BLEServer));
}

// 设置间隔时间
void setIntervalMsecs(uint16_t intervalMSecs){
    ble.intervalMSecs = intervalMSecs;
}

// 设置窗口时间
void setWindowsMsecs(uint16_t windowMSecs){
    ble.windowMSecs = windowMSecs;
}

// 设置扫描间隔时间
void setDuration(uint32_t duration){
    ble.duration = duration;
}

// 设置电池电量
void setBatteryLevel(uint8_t level){
    ble.batteryLevel = level;
}

// 设置电池充电状态
void setBatteryChargeStatus(bool chargeStatus){
    ble.chargeStatus = chargeStatus;
}

// 设置开关状态
void setSwitchStatus(bool switchStatus){
    ble.switchStatus = switchStatus;
}


#endif