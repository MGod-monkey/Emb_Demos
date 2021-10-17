// index.js
// 获取应用实例
var mqtt = require('../../utils/mqtt.min.js')
var client = null
const options = {
  connectTimeout:4000,
  clientID:'mqtt_vscode'
}

Page({
  data: {
    topic:'/test',
    host: '10.34.117.50:8084/mqtt',
    value: '',
    font_size: '28rpx',
    cmd_mess: '消息将在这里显示'
  },
  onLoad() {
    this.connectMQTT()
  },
  changeOption:function(e) {
    // 更换MQTT服务器
    if (e.target.id == "host"){
      console.log("更换host:", e.detail.value);
      client = mqtt.connect('wxs://'+this.data.host, options);
      var size = 28-(e.detail.value.length-22)
      console.log(size)
      client.on('connect', (e)=>{
        console.log('服务器连接成功！')
        this.setData({
          host: e.detail.value,
          font_size: size + 'rpx'
        })
        client.subscribe(this.data.topic, {qos:0},
        (is_error)=>{
          if (!is_error)   console.log('订阅成功！')
        })
      })
    }
    else if(e.target.id == "topic") {
      client.subscribe(e.detail.value, {qos:0},
        (is_error)=>{
          if (!is_error)   
          console.log('订阅成功！')
          this.setData({
            topic: e.detail.value
          })
        })
      }
    this.setData({
      value: ''
    })
  },
  connectMQTT:function() {
    var that = this
    client = mqtt.connect('wxs://'+this.data.host, options);
    client.on('connect', (e)=>{
        console.log('服务器连接成功！')
        client.subscribe(this.data.topic, {qos:0},
        (is_error)=>{
          if (!is_error)   console.log('订阅成功！')
        })
    }),
    client.on('message', function(topic, mess){
      var msg = '收到来自{'+topic+'}的消息:'+mess.toString()
      console.log(msg)
      that.setData({
        cmd_mess: msg
      })
    }),
    client.on('reconnect', (error)=>{
      console.log('正在重连:',error)
    }),
    client.on('error', (error)=>{
      console.log('连接失败:',error)
    })
  },
})
