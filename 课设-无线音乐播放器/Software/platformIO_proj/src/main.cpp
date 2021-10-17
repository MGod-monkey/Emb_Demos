
// /*  ============================================================================================================
//     MrDIY Audio Notifier is a cloud-free media notifier that can play MP3s, stream icecast radios, read text 
//     and play RTTTL ringtones. It is controller over MQTT.

//       Option 1) Connect your audio jack to the Rx and GN pins. Then connect the audio jack to an external amplifier. 
//       Option 2) Use an extenal DAC (like MAX98357A) and uncomment "#define USE_I2S" in the code.


//     + MQTT COMMANDS:  ( 'your_custom_mqtt_topic' is the MQTT prefix defined during the setup)

//       - Play an MP3             MQTT topic: "your_custom_mqtt_topic/play"
//                                 MQTT load: http://url-to-the-mp3-file/file.mp3 
//                                 PS: supports HTTP only, no HTTPS.  

//       - Play an Icecast Stream  MQTT topic: "your_custom_mqtt_topic/stream"
//                                 MQTT load: http://url-to-the-icecast-stream/file.mp3, example: http://22203.live.streamtheworld.com/WHTAFM.mp3

//       - Play a Ringtone         MQTT topic: "your_custom_mqtt_topic/tone"
//                                 MQTT load: RTTTL formated text, example: Soap:d=8,o=5,b=125:g,a,c6,p,a,4c6,4p,a,g,e,c,4p,4g,a

//       - Say Text                MQTT topic: "your_custom_mqtt_topic/say"
//                                 MQTT load: Text to be read, example: Hello There. How. Are. You?

//       - Stop Playing            MQTT topic: "your_custom_mqtt_topic/stop"
      
//       - Change the Volume       MQTT topic: "your_custom_mqtt_topic/volume"
//                                 MQTT load: a double between 0.00 and 1.00, example: 0.7


//     + STATUS UPDATES:

//      - The notifier sends status updates on MQTT topic: "your_custom_mqtt_topic/status" with these values:

//                   "playing"       either paying an mp3, a ringtone or saying a text
//                   "free"          free and waiting for a command
//                   "error"         error when receiving a command: example: MP3 file URL can't be loaded
                  
//      - The LWT MQTT topic: "your_custom_topic/LWT" with values:
//                    "online"       
//                    "offline"    
                                                      
//      - At boot, the notifier plays a 2 second audio chime when it is successfully connected to Wifi & MQTT


//     + SETUP:
     
//       To Upload to an ESP8266 module or board:
      
//         - Set CPU Frequency to 160MHz ( Arduino IDE: Tools > CPU Frequency )
//         - Set IwIP to V2 Higher Bandwidth ( Arduino IDE: Tools > IwIP Variant )
//         - Press "Upload"


//     + DEPENDENCIES:

//      - ESP8266          https://github.com/esp8266/Arduino
//      - ESP8266Audio     https://github.com/earlephilhower/ESP8266Audio
//      - ESP8266SAM       https://github.com/earlephilhower/ESP8266SAM
//      - IotWebConf       https://github.com/prampec/IotWebConf
//      - PubSubClient     https://github.com/knolleary/pubsubclient


//     Many thanks to all the authors and contributors to the above libraries - you have done an amazing job!

//     For more info, please watch my instruction video at https://youtu.be/SPa9SMyPU58
//     MrDIY.ca
    
//   ============================================================================================================== */

// #define DEBUG_FLAG              // 取消注释开启Debug模式，串口台输出内容
#define OPEN_RGB                 // 取消注释开启RGB灯
#define USE_I2S                 // 取消注释输出I2S音频信号

#include "Arduino.h"
#include "boot_sound.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "AudioFileSourceHTTPStream.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioGeneratorWAV.h"
#include "AudioGeneratorRTTTL.h"
#ifdef USE_I2S
#include "AudioOutputI2S.h"
#else
#include "AudioOutputI2SNoDAC.h"
#endif
#include "ESP8266SAM.h"
// #include "IotWebConf.h"
// #include "IotWebConfUsing.h"
#include "SPI.h"
#include <WS2812FX.h>


AudioGeneratorMP3         *mp3 = NULL;
AudioGeneratorWAV         *wav = NULL;
AudioGeneratorRTTTL       *rtttl = NULL;
AudioFileSourceHTTPStream *file_http = NULL;
AudioFileSourcePROGMEM    *file_progmem = NULL;
AudioFileSourceBuffer     *buff = NULL;
#ifdef USE_I2S
AudioOutputI2S            *out = NULL;
#else
AudioOutputI2SNoDAC       *out = NULL;
#endif

// 初识化MQTT服务器 ---------------------------
WiFiClient                wifiClient;
PubSubClient              mqttClient(wifiClient);
#define  port                1883      //MQTT端口号
#define  MQTT_MSG_MAXSIZE    256       //MQTT接收信息最大长度
#define CONNECTOUTTIME       8000   //连接超时时间(单位:ms)
const char* mqttTopicPrefix = "/mgodmonkey"; //主题前缀
const char* willTopic       = "init_mess";    //初识信息的主题：/mgodmonkey/init_mess
const char* willMessage     = "offline";
boolean willRetain          = false;
byte willQoS                = 0;  //MQTT发送机制：0~只发送一次 1~至少发送一次 2~至少发送两次

char mqttServer[32]       = "broker-cn.emqx.io";    //MQTT服务器
char mqttTopic[32];   //MQTT主题
char mqttUserName[16];  //MQTT用户名
char mqttUserPassword[16];  //MQTT用户名密码

// 初识化clientID ---------------------------
#ifdef ESP8266
String clientID = String("ESP8266-") +String(random(0xffff), HEX);
#elif ESP32
String clientID = String("ESP32") + String((uint32_t) ESP.getEfuseMac(), HEX);
#endif

// 初识化WS2812灯珠 ---------------------------
#ifdef OPEN_RGB
  #define LED_COUNT 1 // 灯珠数量
  #define LED_PIN 4   // 数据引脚
  #define NORMAL_BRIGHTNESS 96  // 最大亮度 0~255
  #define NORMAL_SPEED  1000  // 默认呼吸灯速率 10~65535
  #define CMD_CLOSE  0   // 微信小程序指令：关闭灯
  #define CMD_START  1  // 打开灯
  #define CMD_PAUSE  2  // 暂停灯
  #define CMD_STATIC 3  // 固定灯
  #define CMD_BLINK  4  // 闪烁灯
  #define CMD_BREATH 5  // 呼吸灯
  #define CMD_PARTY_BLINKE  6  // 炫彩夺目灯(闪烁版)
  #define CMD_PARTY_BREATH  7  // 炫彩夺目灯(呼吸版)
  WS2812FX WS2812 = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#endif


// 初识化wifi ---------------------------
const char* ssid = "mi"; //wifi ssid
const char* password = "wpq5201314";  //wifi密码

// 初识化播放器 ---------------------------
float volume_level              = 0.8;  //音量：0~1.0
String playing_status;
const int preallocateBufferSize = 2048;
void *preallocateBuffer = NULL;

unsigned long startTime;



// 声明函数
void mqttConnect();
void messAlergLED();
void playBootSound();
void stopPlaying();
void setup_wifi();
char* mqttFullTopic(const char action[]);
void broadcastStatus(const char topic[], String msg);
void onMqttMessage(char* topic, byte* payload, unsigned int mlength);
#ifdef OPEN_RGB
  void setRGB(uint8_t color[]);
  void stopRGB();
  void setRGB(uint8_t color[], uint8_t cmd);
  void setRGB(uint8_t color[], uint16_t speed, uint8_t brightness, uint8_t cmd);
#endif


/* ################################## Setup ############################################# */

void setup() {

  Serial.begin(115200);

  #ifdef LED_Pin
    pinMode(LED_Pin, OUTPUT); 
    // updateLEDBrightness(10);
    iotWebConf.setStatusPin(LED_Pin);
  #endif


  #ifdef USE_I2S
    out = new AudioOutputI2S();
    #ifdef DEBUG_FLAG
    Serial.print("[MSG] Using I2S output!\n");
    #endif
  #else
    out = new AudioOutputI2SNoDAC();
    #ifdef DEBUG_FLAG
    Serial.print("[MSG] Using No DAC - using Serial port Rx pin!\n");
    #endif
  #endif
    out->SetGain(volume_level);

  #ifdef OPEN_RGB
    WS2812.init();
    WS2812.setBrightness(NORMAL_BRIGHTNESS);
    WS2812.setSpeed(NORMAL_SPEED);
    WS2812.setColor(CYAN);
    WS2812.setMode(FX_MODE_MULTI_STROBE);
    WS2812.start();
    WS2812.show();
  #endif

    mqttClient.setServer(mqttServer, port);
    mqttClient.setCallback(onMqttMessage);
    mqttClient.setBufferSize(MQTT_MSG_MAXSIZE);
}

/* ##################################### Loop ############################################# */

void loop() {
  #ifdef OPEN_RGB
    WS2812.service();
  #endif

  if (WiFi.status() == WL_CONNECTED){
    if (!mqttClient.connected())   mqttConnect();
    mqttClient.loop();
    if (mp3   && !mp3->loop())    stopPlaying();
    if (wav   && !wav->loop())    stopPlaying();
    if (rtttl && !rtttl->loop())  stopPlaying();
  }
  else setup_wifi();

}

/* ############################### 音乐播放器 ############################################ */
//播放提示音
void playBootSound() {
  file_progmem = new AudioFileSourcePROGMEM(boot_sound, sizeof(boot_sound));
  wav = new AudioGeneratorWAV();
  wav->begin(file_progmem, out);
}

void stopPlaying() {
  #ifdef DEBUG_FLAG
    Serial.print("[MSG] Interrupted!\n");
  #endif
  if (mp3) {
    mp3->stop();
    delete mp3;
    mp3 = NULL;
  }
  if (wav) {
    wav->stop();
    delete wav;
    wav = NULL;
  }
  if (rtttl) {
    rtttl->stop();
    delete rtttl;
    rtttl = NULL;
  }
  if (buff) {
    buff->close();
    delete buff;
    buff = NULL;
  }
  if (file_http) {
    file_http->close();
    delete file_http;
    file_http = NULL;
  }
  if (file_progmem) {
    file_progmem->close();
    delete file_progmem;
    file_progmem = NULL;
  }
  broadcastStatus("status", "free");
}

/* ################################## MQTT服务器 ############################################### */

/*---------------- 初识化WiFi ------------------*/
void setup_wifi() {

  #ifdef DEBUG_FLAG
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  #endif // DEBUG

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    #ifdef DEBUG_FLAG
      Serial.print(".");
    #endif
    if (millis() - startTime > CONNECTOUTTIME){
      #ifdef DEBUG_FLAG
        Serial.print("\nConnect failed，try again in 5s！");
      #endif
      #ifdef OPEN_RGB
        WS2812.setMode(FX_MODE_STATIC);
        WS2812.setColor(RED);
        WS2812.show();
      #endif
      break;
    }
    delay(500);
    #ifdef OPEN_RGB
      WS2812.show();
    #endif
  }
  if (WiFi.status() == WL_CONNECTED){
    #ifdef DEBUG_FLAG
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    #endif
    return;
  }
  delay(5000);
}

/*---------------- 订阅主题回调函数 ------------------*/
void onMqttMessage(char* topic, byte* payload, unsigned int mlength)  {

  char newMsg[MQTT_MSG_MAXSIZE];

  if (mlength > 0) {
    memset(newMsg, '\0' , sizeof(newMsg));
    memcpy(newMsg, payload, mlength);

  #ifdef DEBUG_FLAG
    Serial.print("\n");
    Serial.print("[MQTT] topic{");
    Serial.print(topic);
    Serial.print("} get msg: ");
    Serial.print(newMsg);
    Serial.print("\n");
  #endif

    // 接收到主题：/mgodmonkey/play 的消息
    if ( !strcmp(topic, mqttFullTopic("play") ) ) {
      stopPlaying();
      file_http = new AudioFileSourceHTTPStream();
      if ( file_http->open(newMsg)) {
        broadcastStatus("status", "playing");
        // updateLEDBrightness(50); 
        buff = new AudioFileSourceBuffer(file_http, preallocateBuffer, preallocateBufferSize);
        mp3 = new AudioGeneratorMP3();
        mp3->begin(buff, out);
      } else {
        stopPlaying();
        broadcastStatus("status", "error");
        broadcastStatus("status", "free");
      }
    }


    // 接收到主题：/mgodmonkey/tone 的消息
    if ( !strcmp(topic, mqttFullTopic("tone") ) ) {
      stopPlaying();
      broadcastStatus("status", "playing");
      // updateLEDBrightness(50);
      file_progmem = new AudioFileSourcePROGMEM( newMsg, sizeof(newMsg) );
      rtttl = new AudioGeneratorRTTTL();
      rtttl->begin(file_progmem, out);
      broadcastStatus("status", "free");
    }

    // 接收到主题：/mgodmonkey/say 的消息
    if ( !strcmp(topic, mqttFullTopic("say"))) {
      stopPlaying();
      broadcastStatus("status", "playing");
      // updateLEDBrightness(50);
      ESP8266SAM *sam = new ESP8266SAM;
      sam->Say(out, newMsg);
      delete sam;
      stopPlaying();
      broadcastStatus("status", "free");
    }

    // 接收到主题：/mgodmonkey/volume 的消息
    if ( !strcmp(topic, mqttFullTopic("volume"))) {
      volume_level = atof(newMsg);
      if ( volume_level < 0.0 ) volume_level = 0;
      if ( volume_level > 1.0 ) volume_level = 0.8;
      out->SetGain(volume_level);
    }

    // 接收到主题：/mgodmonkey/stop 的消息
    if ( !strcmp(topic, mqttFullTopic("stop"))) {
      stopPlaying();
      broadcastStatus("status", "free");
    }
    
    // 接收到主题：/mgodmonkey/getDeviceStatus 的消息
    if ( !strcmp(topic, mqttFullTopic("getDeviceStatus"))) {
      broadcastStatus("deviceMsg", String("IP:") + WiFi.localIP().toString());
    }

    // 接收到主题：/mgodmonkey/rgb 的消息 
    // 格式：color_r, color_g, color_b, brightness, speed, cmd
    // 示例：64,245,68,64,500,3
    if ( !strcmp(topic, mqttFullTopic("rgb"))) {
      #ifdef OPEN_RGB
        char *p;uint8_t color_RGB[3];uint8_t cmd;uint8_t brightness;uint16_t speed;int i=0;
        p = strtok(newMsg, ",");
        while(p){
          switch (i){
          case 0: case 1: case 2: color_RGB[i] = (uint8_t)atoi(p);break;
          case 3: brightness = (uint8_t)atoi(p);break;
          case 4: speed = (uint16_t)atoi(p);break;
          default: cmd = (uint8_t)atoi(p);break;
          }
          i++;
          p=strtok(NULL, ",");
        }
        switch (cmd){
          case CMD_CLOSE: WS2812.stop();break;
          case CMD_START: WS2812.start();break;
          case CMD_PAUSE: WS2812.pause();break;
          case CMD_STATIC: setRGB(color_RGB);break;
          case CMD_BLINK: setRGB(color_RGB, speed, brightness, FX_MODE_BLINK);break;
          case CMD_BREATH: setRGB(color_RGB, speed, brightness, FX_MODE_BREATH);break;
          case CMD_PARTY_BLINKE: setRGB(color_RGB, speed, brightness, FX_MODE_RAINBOW_CYCLE);break;
          case CMD_PARTY_BREATH: setRGB(color_RGB, speed, brightness, FX_MODE_COLOR_WIPE_RANDOM);break;
          default:
            #ifdef DEBUG_FLAG
              Serial.print("[error] Unknown CMD!");
            #endif
            break;
        }
    #endif
    #ifndef OPEN_RGB && #ifdef DEBUG_FLAG 
      Serial.print("[error] RGB switch not open!");
    #endif
    }
  }
}


/*---------------- 向主题推送消息函数 ------------------*/
void broadcastStatus(const char topic[], String msg) {

  if ( playing_status != msg) {
    char charBuf[msg.length() + 1];
    msg.toCharArray(charBuf, msg.length() + 1);
    mqttClient.publish(mqttFullTopic(topic), charBuf);
    playing_status = msg;

    #ifdef DEBUG_FLAG
    Serial.print("[MQTT] Topic{");
    Serial.print(mqttFullTopic(topic));
    Serial.print("} send msg: ");
    Serial.print(msg.c_str());
    Serial.print("\n");
    #endif
  }
}



/*---------------- MQTT服务器连接函数 ------------------*/
void mqttConnect() {
  while (!mqttClient.connected()) {
    // updateLEDBrightness(0);
    if (mqttClient.connect(clientID.c_str(), mqttUserName, mqttUserPassword, mqttFullTopic(willTopic), willQoS, willRetain, willMessage)) {
      mqttClient.subscribe(mqttFullTopic("play"));
      mqttClient.subscribe(mqttFullTopic("tone"));
      mqttClient.subscribe(mqttFullTopic("say"));
      mqttClient.subscribe(mqttFullTopic("rgb"));
      mqttClient.subscribe(mqttFullTopic("stop"));
      mqttClient.subscribe(mqttFullTopic("volume"));
      mqttClient.subscribe(mqttFullTopic("getDeviceStatus"));
      
      #ifdef DEBUG_FLAG
        Serial.print("[MSG] Connected to MQTT\n");
      #endif

      broadcastStatus("deviceMsg", "server_status: online");
      broadcastStatus("deviceMsg", String("MQTTServer:") + String(mqttServer));
      broadcastStatus("deviceMsg", String("IP:") + WiFi.localIP().toString());
      broadcastStatus("status", "free");
      playBootSound();
      #ifdef OPEN_RGB
        WS2812.setMode(FX_MODE_RAINBOW_CYCLE);
        WS2812.show();
      #endif
    }
  }
}

/*---------------- 给MQTT主题名添加前缀------------------*/
char* mqttFullTopic(const char action[]) {
  strcpy (mqttTopic, mqttTopicPrefix);
  strcat (mqttTopic, "/");
  strcat (mqttTopic, action);
  return mqttTopic;
}

#ifdef OPEN_RGB
  /*---------------- 设置RGB ------------------*/
  void setRGB(uint8_t color[]) {
    WS2812.clear();
    WS2812.setMode(FX_MODE_STATIC);
    WS2812.setColor(color[0], color[1], color[2]);
    if (!WS2812.isRunning()) {WS2812.start();}
    WS2812.show();
  }

  void setRGB(uint8_t color[], uint8_t cmd) {
    WS2812.clear();
    WS2812.setMode(cmd);
    WS2812.setColor(color[0], color[1], color[2]);
    if (!WS2812.isRunning()) {WS2812.start();}
    WS2812.show();
  }

  void setRGB(uint8_t color[], uint16_t speed, uint8_t brightness, uint8_t cmd) {
    WS2812.clear();
    WS2812.setColor(color[0], color[1], color[2]);
    WS2812.setSpeed(speed);
    WS2812.setBrightness(brightness);
    WS2812.setMode(cmd);
    if (!WS2812.isRunning()) {WS2812.start();}
    WS2812.show();
  }
#endif