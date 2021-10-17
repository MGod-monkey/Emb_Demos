// index.js
const app = getApp();
var mqtt = require('../../utils/mqtt.js')
var options = {
  keepalive: 1,
  clear: false,
  connectTimeout: 5000, //mqtt连接超时时间，ms
  reconnectPeriod: 0, //取消自动重连
  clientID:'Client_WX_' + Math.random().toString(16).substr(2, 4)
}
var MQTTHost = app.globalData.MQTTServer + ":" + app.globalData.MQTTPort + "/mqtt"

// 获取应用实例
Page({
  data: {
    //服务器信息
    MQTTHost: MQTTHost,
    topic: app.globalData.topic,
    mqttStatusCode: app.globalData.mqttStatusCode,
    topicStatusCode: app.globalData.topicStatusCode,
    deviceIP: app.globalData.deviceIP,
    // reconnectNum: 0,
    deviceIsConnected: false,
    //播放器信息
    mp3Sample: "",
    deviceIsFree: app.globalData.deviceIsFree,
    saySample: "hello,i am the author,i am fine,and you?",
    rtttlSample: "don'tcare:d=4,o=5,b=125:16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d",
    playingMP3: false,
    playingRtttl: false,
    playingSay: false,
    mp3Content: "",
    rtttlContent: "",
    sayContent: "",
    //弹窗信息
    showModal: false,
    changeMess: "",
    changeType: "host",
    //下拉框示例
    selectArray: [],
  },
  onLoad() {
    this.initSongList()
    this.connectMQTT()
  },
  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
    //调用刷新时将执行的方法
    this.onRefresh();
  },
  // 初识化歌单
  initSongList: function() {
    // 获取歌单
    var that = this
    var songPHP = 'http://' + app.globalData.serverIP + '/getSongList.php'  //获取歌单的脚本
    wx.request({
      url: songPHP,
      header: {
        'content-type': 'application/json' // 默认值
      },
      success (res) {
        console.log('初识化歌单成功！')
        var num = res.data['num']
        var name, songer, selectArray = []
        for (var i=1; i <= num; i++){
          name = res.data['songs'][i-1].split('/').pop()
          name = name.split('.')[0]
          songer = name.split('-').length==2?name.split('-')[1]:''
          name = name.split('-')[0]
          selectArray.push({
            'id': i,
            'name': name,
            'songer': songer,
            'url': res.data['songs'][i-1]
          })
        }
        that.setData({
          selectArray: selectArray
        })
        },
      fail (error){
        console.log('初识化歌单失败！--',error)
      }
      })
    },
  //连接MQTT服务器
  connectMQTT:function() {
    var that = this
    this.setData({
      mqttStatusCode: 0,
    }),
    app.globalData.client = mqtt.connect("wx://" + this.data.MQTTHost, options)
    app.globalData.client.on('connect', (e)=>{
        console.log('服务器连接成功！')
        that.setData({
          mqttStatusCode: 1
        })
      setTimeout(function () {
        that.mqttSubscribe("")
        that.mqttSubscribe("/deviceMsg")
        that.mqttSubscribe("/play")
        that.mqttSubscribe("/tone")
        that.mqttSubscribe("/say")
        that.mqttSubscribe("/status")
        that.mqttSubscribe("/volume")
        that.mqttSubscribe("/stop")
        }, 500)
    }),
    // 处理MQTT消息
    app.globalData.client.on('message', function(topic, mess){
      var msg = mess.toString()
      console.log('收到来自{'+topic+'}的消息:' + msg)
      if (topic == that.data.topic + "/deviceMsg"){
        var type = msg.slice(0, 2)
        if (type == "IP"){
          var ip = msg.slice(3)
          app.globalData.deviceIP = ip
          that.setData({
            deviceIP: ip,
            deviceIsConnected: true
          })
          }
        }
        else if (topic == that.data.topic + "/status"){
          if (msg == "free" || msg == "error") that.setFree()
          else that.setNoFree('play')
        }
    }),
    // app.globalData.client.on('reconnect', (error)=>{
    //   console.log("连接失败：",error)
    //   that.setData({
    //     mqttStatus: "error",
    //     topicStatus: "error",
    //     deviceIsConnected: false
    //   })
    //   app.globalData.client.end()
    // }),
    app.globalData.client.on('error', (error)=>{
      console.log('连接失败:',error)
      that.setData({
        mqttStatusCode: -1,
        topicStatusCode: -1,
        deviceIsConnected: false
      })
    })
    setTimeout(function(){
      // 服务器连接失败
      if (!app.globalData.client.connected){
      console.log('连接失败')
        that.setData({
          mqttStatusCode: -1,
          topicStatusCode: -1,
          deviceIsConnected: false
        })}
    }, options.connectTimeout)
  },
  //按钮重连事件
  mqttReconnect:function(e) {
    console.log("正在重连...")
    this.setData({
      mqttStatusCode: 0,
      topicStatusCode: 0
    })
    // 3s后重连
    setTimeout(function(){
      app.globalData.client.reconnect()
    }, 3000)
    // else {
    //   wx.showModal({
    //     title: "温馨提示", // 提示的标题
    //     content: "由于小程序限制，无法再次进行重连，请检查MQTT地址后再次进入小程序", // 提示的内容
    //     showCancel: false, // 是否显示取消按钮，默认true
    //     confirmText: "我已知晓", // 确认按钮的文字，最多4个字符
    //     confirmColor: "#576B95", // 确认按钮的文字颜色，必须是 16 进制格式的颜色字符串
    // })
    // }
  },
    //刷新
  onRefresh(){
    //在当前页面显示导航条加载动画
    wx.showNavigationBarLoading(); 
    //显示 loading 提示框。需主动调用 wx.hideLoading 才能关闭提示框
    wx.showLoading({
      title: '刷新中...',
    })
    this.sendCmd("getDeviceStatus", "gkd")
    this.initSongList() //更新歌单
    setTimeout(function(){
        //隐藏loading 提示框
        wx.hideLoading();
        //隐藏导航条加载动画
        wx.hideNavigationBarLoading();
        //停止下拉刷新
        wx.stopPullDownRefresh();
    }, 1500)
  },
   //显示模块对话框
   showModal: function(e) {
    this.setData({
      changeType: e.target.id,
      showModal: true
    })
    // console.log(this.data.changeType)
  },
  //隐藏模块对话框
  hideModal: function() {
   this.setData({
      showModal: false
    })
  },
  // 对话框取消按钮点击事件
  onCancel: function() {
    this.hideModal();
  },
   // 输入框内容改变事件
  inputChange: function(e) {
    this.setData({
      changeMess: e.detail.value
    })
  },
  //  对话框确认按钮点击事件
  onConfirm: function() {
    this.hideModal()
    var that = this
    if (this.data.changeMess != "" && this.data.changeType == "topic"){
      this.mqttUnSubscribe()
      app.globalData.topic = this.data.changeMess
      app.globalData.deviceIP = ""
      this.setData({
        topic:this.data.changeMess,
        topicStatusCode: 0,
        deviceIsConnected: false,
        deviceIP: ""
      })
      wx.showToast({
        title: '修改成功',
        icon: 'success',
        mask: true,
        duration: 1500//持续的时间
      })
      this.mqttSubscribe("")
      this.mqttSubscribe("/deviceMsg")
      this.mqttSubscribe("/play")
      this.mqttSubscribe("/tone")
      this.mqttSubscribe("/say")
      this.mqttSubscribe("/rgb")
      this.mqttSubscribe("/status")
      this.mqttSubscribe("/volume")
      this.mqttSubscribe("/stop")
    }
    else if(this.data.changeMess != "" && this.data.changeType == "host"){
      var arr = this.data.changeMess.split(":")
      var host = arr[0]
      var port = arr[1].split("/")[0]
      app.globalData.MQTTServer = host
      app.globalData.MQTTPort = port
      app.globalData.deviceIP = ""
      wx.showToast({
        title: '修改成功',
        icon: 'success',
        mask: true,
        duration: 1500//持续的时间
      })
      this.setData({
        MQTTHost:this.data.changeMess,
        topicStatusCode: 0,
        mqttStatusCode: 0,
        deviceIsConnected: false,
        deviceIP: ""
      })
      if (app.globalData.client.connected) {
        this.sendCmd("stop", "stop")
        this.setFree()
        app.globalData.client.end()
      }
      setTimeout(function(){
        that.connectMQTT()
      }, 1500)
    }
  },
  //下载示例文件
  downloadSampleFile:function (e){
    var fileURL = 'http://' + app.globalData.serverIP + '/' + e.detail.cmd + '.txt'
    if ((app.globalData.filePaths[0]=='' && e.detail.cmd == 'rtttlSample')
          || (app.globalData.filePaths[1]=='' && e.detail.cmd == 'saySample')){
      wx.showLoading({
        title: '加载中',
        icon: 'loading',
        duration: 8000
      })
      wx.downloadFile({
        url: fileURL,
        success(res) {
          e.detail.cmd == "saySample" ? app.globalData.filePaths[1] = res.tempFilePath:app.globalData.filePaths[0] = res.tempFilePath
          wx.openDocument({
            showMenu: true,
            filePath: res.tempFilePath,
            success: (res) => {
              wx.hideLoading()
              console.log('读取成功!', res)
            },
            fail: (err) => {
              console.log('读取失败!', err)
              wx.hideLoading()
              wx.showToast({
                title: '打开文件失败',
                icon: 'error',
                duration: 1000
              })
            }
          })},
        fail(err){
          wx.hideLoading()
          wx.showToast({
            title: '下载文件失败',
            icon: 'error',
            duration: 1000
          })
        }}
      )
    }
    else if (app.globalData.filePaths[0] && e.detail.cmd == 'rtttlSample'){
      wx.openDocument({
        showMenu: true,
        filePath: app.globalData.filePaths[0],
        success: (res) => {
          wx.hideLoading()
          console.log('读取成功!', res)
        },
        fail: (err) => {
          console.log('读取失败!', err)
          wx.hideLoading()
          wx.showToast({
            title: '打开文件失败',
            icon: 'error',
            duration: 1000
          })
        }})
    }
    else if (app.globalData.filePaths[1] && e.detail.cmd == 'saySample'){
      wx.openDocument({
        showMenu: true,
        filePath: app.globalData.filePaths[1],
        success: (res) => {
          wx.hideLoading()
          console.log('读取成功!', res)
        },
        fail: (err) => {
          console.log('读取失败!', err)
          wx.hideLoading()
          wx.showToast({
            title: '打开文件失败',
            icon: 'error',
            duration: 1000
          })
        }
        })
    }
  },

  // 获取主题全称
  getFullTopic:function(cmd){
    return this.data.topic + cmd 
  },

  // 主题订阅事件
  mqttSubscribe:function(cmd){
    var full_topic = this.getFullTopic(cmd)
    app.globalData.client.subscribe(full_topic, {qos:0},
    (is_error)=>{
      if (!is_error){   
      console.log('Topic: '+full_topic+'订阅成功！')
      this.setData({
        topicStatusCode: 1
      })}
      else {
        console.log('Topic: '+full_topic+'订阅失败！')
        this.setData({
          topicStatusCode: -1
        })}
    })
  },

  // 主题取消订阅事件
  mqttUnSubscribe:function() {
    app.globalData.client.unsubscribe(this.getFullTopic(""))
    app.globalData.client.unsubscribe(this.getFullTopic("/deviceMsg"))
    app.globalData.client.unsubscribe(this.getFullTopic("/play"))
    app.globalData.client.unsubscribe(this.getFullTopic("/tone"))
    app.globalData.client.unsubscribe(this.getFullTopic("/say"))
    app.globalData.client.unsubscribe(this.getFullTopic("/status"))
    app.globalData.client.unsubscribe(this.getFullTopic("/volume"))
    app.globalData.client.unsubscribe(this.getFullTopic("/stop"))
  },

  //向MQTT发送指令
  sendCmd:function(topic, cmd){
    var that = this
    var topic = that.data.topic + "/" + String(topic)
    setTimeout(function (){
    app.globalData.client.publish(topic, String(cmd), {
      qos:0, rein: false
    })
    }, 500) //延时500ms,防止指令发送过于密集
    console.log("[send]" + topic + ": " + String(cmd))
  },

  // 下拉框点击事件
  setUrl: function(e){
    this.setData({
      mp3Content: e.detail
    })
  },

  // 输入框输入内容事件
  changeRtttlContent:function(e){
    this.setData({
      rtttlContent: e.detail.value
    })
  },
  changeSayContent:function(e){
    this.setData({
      sayContent: e.detail.value
    })
  },

  //设置为空闲状态
  setFree:function(){
    app.globalData.deviceIsFree = true
    this.setData({
      deviceIsFree: true,
      playingMP3: false,
      playingRtttl: false,
      playingSay: false
    })
  },

  //设置为忙碌状态
  setNoFree:function(type){
    app.globalData.deviceIsFree = false
    this.setData({
      deviceIsFree: false,
      playingMP3: type=="play"?true:false,
      playingRtttl: type=="tone"?true:false,
      playingSay: type=="say"?true:false
    })
  },

  //设置音量
  setVolume:function(e){
    this.sendCmd("volume", e.detail.value/100)
  },

  //暂停或停止播放
  playOrStop:function(e){
    //服务器或设备未连接时
    if (this.data.mqttStatusCode != 1 || !this.data.deviceIsConnected){
      wx.showModal({
        title: "温馨提示", // 提示的标题
        content: "MQTT服务器或设备不在状态呢！请喝瓶脉动后再试试吧", // 提示的内容
        showCancel: false, // 是否显示取消按钮，默认true
        confirmText: "确认", // 确认按钮的文字，最多4个字符
        confirmColor: "#000000", // 确认按钮的文字颜色，必须是 16 进制格式的颜色字符串
    })
    }
    // 播放器处于空闲状态时
    else if (app.globalData.deviceIsFree && e.detail.cmd == "play") {
      if (e.detail.cmdType == "play"){
        if (this.data.mp3Content != "") this.sendCmd(e.detail.cmdType, this.data.mp3Content)
        else this.sendCmd(e.detail.cmdType, this.data.mp3Sample)
        this.setNoFree("play")
      }
      else if (e.detail.cmdType == "tone"){
        if (this.data.rtttlContent != "") this.sendCmd(e.detail.cmdType, this.data.rtttlContent)
        else this.sendCmd(e.detail.cmdType, this.data.rtttlSample)
        this.setNoFree("tone")
      }
      else {
        if (this.data.sayContent != "") this.sendCmd(e.detail.cmdType, this.data.sayContent)
        else this.sendCmd(e.detail.cmdType, this.data.saySample)
        this.setNoFree("say")
      }}
    // 播放器处于忙碌状态时
    else if (!app.globalData.deviceIsFree && e.detail.cmd == "play") {
      this.sendCmd("stop", "stop")
      this.setFree()
      if (e.detail.cmdType == "play"){
        if (this.data.mp3Content != "") this.sendCmd(e.detail.cmdType, this.data.mp3Content)
        else this.sendCmd(e.detail.cmdType, this.data.mp3Sample)
        this.setNoFree("play")
      }
      else if (e.detail.cmdType == "tone"){
        if (this.data.rtttlContent != "") this.sendCmd(e.detail.cmdType, this.data.rtttlContent)
        else this.sendCmd(e.detail.cmdType, this.data.rtttlSample)
        this.setNoFree("tone")
      }
      else {
        if (this.data.sayContent != "") this.sendCmd(e.detail.cmdType, this.data.sayContent)
        else this.sendCmd(e.detail.cmdType, this.data.saySample)
        this.setNoFree("say")
      }}
    // 暂停播放
    else {
      this.sendCmd("stop", "stop")
      this.setFree()
    }
  }
})
