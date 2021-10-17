// pages/contact/contact.js
const app = getApp();
const dateTime = new Date();
const md5 = require('../../utils/md5.js');

var inputVal = '';
var msgList = [];
var windowWidth = wx.getSystemInfoSync().windowWidth;
var windowHeight = wx.getSystemInfoSync().windowHeight * (750 / windowWidth);
const cmdList = ['/play', '/say', '/tone', '/volume', '/stop', '/rgb'];
var keyHeight = 0;
const appid = '6acacd086a345bfcc844e02bbb1c1ffa'  //思知机器人ID：https://console.ownthink.com/dashboard
// 语音合成配置，采用阿里云接口，文档见https://help.aliyun.com/document_detail/84425.html
var ttsUrl = 'http://' + app.globalData.serverIP + '/tts.php'
var option = {
   'sample_rate': 16000,  //采样率
   'volume': 100, //音量 0~100
   'voice': 'maoxiaomei', //发音人
   'speech_rate': -20,   //语速 -500~500
   'pitch_rate': 25    //语调   -500~500
}

/**
 * 初始化数据
 */
function initData(that) {
 inputVal = '';
 msgList = [{
   speaker: 'server',
   contentType: 'text',
   content: '你好，我是钦钦，你的臭宝！我能陪你聊天，中英翻译，发送MQTT指令！指令格式为"/MQTT指令:指令内容" 试着发送下面这条指令给我看看吧！',
   time: 0,
   error: ''
  },
  {
   speaker: 'server',
   contentType: 'text',
   content: '/say:hello, I am the author, are you ok?',
   time: 0,
   error: ''
  }
 ]
 that.setData({
  msgList,
  inputVal,
  time: dateTime.toLocaleString()
 })
}


Page({

 /**
  * 页面的初始数据
  */
 data: {
  scrollHeight: '92vh',
  screenHeight: 0,
  inputBottom: 0,
  time: '',
  toView: 'msg-0',
  author: app.globalData.author,
  hasUserInfo: false,
  isCloseError: false,
  canIUse: wx.canIUse('button.open-type.getUserInfo'),
  canIUseGetUserProfile: false,
  canIUseOpenData: wx.canIUse('open-data.type.userAvatarUrl') && wx.canIUse('open-data.type.userNickName') // 如需尝试获取用户信息可改为false
 },

 /**
  * 生命周期函数--监听页面加载
  */
 onLoad: function(options) {
  initData(this)
  if (wx.getUserProfile) {
    this.setData({
      canIUseGetUserProfile: true
    })
  }
  this.setData({
   cusHeadIcon: '../../icons/author.png',
  });
 },

   //获取用户信息
  getUserProfile(e) {
  wx.getUserProfile({
    desc: '获取用户头像',
    success: (res) => {
      this.setData({
        userInfo: res.userInfo,
        hasUserInfo: true
      })
    }
  })
  },

 /**
  * 获取聚焦
  */
 focus: function(e) {
  if (e.detail.height != 0)
    var keyHeight = e.detail.height * (750 / windowWidth) - 108
  else {var keyHeight = 0}
  this.setData({
   toView: 'msg-' + (msgList.length - 1),
   inputBottom: keyHeight,
   scrollHeight: windowHeight - keyHeight - 42
  })
  this.goBottom()
 },

 /**
  * 回滚到最底部消息
  */
 goBottom:function() {
  this.setData({
    toView: 'msg-' + (msgList.length - 1),
   })
 },

 //失去聚焦(软键盘消失)
 blur: function(e) {
  this.setData({
   scrollHeight: '90vh',
   inputBottom: 0
  })
  this.goBottom()
 },

/**
 * 跟新输入框的值
 */
 changeMsg: function(e){
    this.setData({
      inputVal: e.detail.value
    })
 },
 /**
  * 发送点击监听
  */
 sendClick: function(e) {
  var timestamp = (new Date()).valueOf()  //获取当前时间撮
  if (this.data.inputVal){
    msgList.push({
    speaker: 'customer',
    contentType: 'text',
    time: timestamp,
    timeFormat: this.getTimeFormat(timestamp),
    content: this.data.inputVal
    })
    this.handlerMsg(this.data.inputVal)
    inputVal = '';
    this.setData({
    msgList,
    inputVal
    })
    this.goBottom()
  }
 },
 /**
  * 处理用户发送的消息 
  */
 handlerMsg: function(text){
   if (cmdList.indexOf(text.trim().split(':')[0]) != -1) {
      const topic = app.globalData.topic + text.trim().split(':')[0]
      app.globalData.client.publish(topic, text.trim().split(':')[1], {
        qos:0, rein: false
      })
      return ;
   }
   var that = this
   wx.request({
     url: 'https://api.ownthink.com/bot',
     data: {
       spoken: text,
       appid: appid,
       userid: 'WX_Reboot_007'  //固定的ID可以连接上下文
     },
     timeout: 5000,
     mothod: 'POST',
     success (res) {
      that.tts(res.data.data.info.text)
    },
    error (err){
      that.showDebug('机器人不在状态')
      that.sendBackMsg('滴~俺掉线了！', timestamp, '机器人不在状态')
    }
  })
  that.goBottom()
 },
  /**
  * 发送返回信息
  */
 sendBackMsg: function(text, time, error) {
    msgList.push({
    speaker: 'server',
    contentType: 'text',
    content: text,
    error: error,
    time: time,
    timeFormat: this.getTimeFormat(time) 
    })
    this.setData({msgList})
    this.goBottom()
 },

 // 时间撮格式化
 getTimeFormat: function(time) {
   if (time.toString().length != 13) time = time * 1000 
    var date = new Date(time)
    const Y = date.getUTCFullYear()
    const M = date.getMonth()
    const D = date.getDate()
    const h = date.getHours()<10?('0'+date.getHours()):date.getHours()
    const m = date.getMinutes()<10?('0'+date.getMinutes()):date.getMinutes()
    const s = date.getSeconds()<10?('0'+date.getSeconds()):date.getSeconds()
    return h + ":" + m + ':' + s
 },

 // 处理语言合成结果
 handleTTS: function(text, result) {
  if (!result.isOK){
    this.showDebug(result.error)
    this.sendBackMsg(text, result.timestamp, result.error)
  }
  else this.sendBackMsg(text, result.timestamp, '')
 },

 // 语音合成
 tts: function(text){
    const that = this
    var result = {
      isOK: true,
      timestamp: 0,
      error: ''
    }
    wx.request({
      url: ttsUrl,
      method: 'POST',
      timeout: 10 * 1000,
      data: {
        'text': text,
        'volume': option['volume'],
        'voice': option['voice'],
        'sample_rate': option['sample_rate'],
        'speech_rate': option['speech_rate'],
        'pitch_rate': option['pitch_rate']
      },
      header: {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      success (res){
        if (res.data.error){
          reslut.isOK = false
          reslut.timestamp = res.data.time
          result.error = '语言合成失败:'+res.data.reason
        }
        else {
          if (!that.sendUrl(res.data.audio_url)){
            result.isOK = false
            result.timestamp = res.data.time
            result.error = '设备不在状态'
          }
        }
        that.handleTTS(text, result)
      },
      error (err){
        reslut.isOK = false
        reslut.timestamp = res.data.time
        result.error = '语言合成失败'+err
        that.handleTTS(text, result)
      }
    })
  },
  // // MD5加密获取文件名
  // getFileNameByMD5:function(text){
  //   return 'http://' + app.globalData.serverIP + '/tts/' + md5.hexMD5(text).substr(8, 16) + '.' + option['format']
  // },
  //向MQTT发送合成语音URL
  sendUrl:function(audioUrl){
    var playTopic = app.globalData.topic + '/play'
    var stopTopic = app.globalData.topic + '/stop'
    if (app.globalData.deviceIP == ''){ return false }
    if (!app.globalData.deviceIsFree){
      app.globalData.client.publish(stopTopic, 'gkd', {qos:0, rein: false})
    }
    app.globalData.client.publish(playTopic, audioUrl, {qos:0, rein: false})
    return true
  },
  // 在聊天框显示或调试器显示
  showDebug: function(text){
    if (this.data.isCloseError){ console.log(text) }
  }
})