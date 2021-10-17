// index.js
const app = getApp();

Page({
  data: {
    userInfo: {},
    // 项目信息
    name: "WiFi音乐播放器",
    version: app.globalData.version,
    MQTTServer: app.globalData.MQTTServer,
    MQTTPort: app.globalData.MQTTPort,
    deviceIP: app.globalData.deviceIP,
    topic: app.globalData.topic,
    author: app.globalData.author,
    email: app.globalData.email,
    github: app.globalData.github,
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    canIUseGetUserProfile: false,
    canIUseOpenData: wx.canIUse('open-data.type.userAvatarUrl') && wx.canIUse('open-data.type.userNickName') // 如需尝试获取用户信息可改为false
  },
  onLoad() {
    if (wx.getUserProfile) {
      this.setData({
        canIUseGetUserProfile: true
      })
    }
  },
  // 生命周期函数--监听页面显示
  onShow: function () {
    this.setData({
      MQTTServer: app.globalData.MQTTServer,
      MQTTPort: app.globalData.MQTTPort,
      deviceIP: app.globalData.deviceIP,
      topic: app.globalData.topic
    })
  },
  //获取用户信息
  getUserProfile(e) {
    wx.getUserProfile({
      desc: '获取用户头像',
      success: (res) => {
        console.log(res)
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    })
  },
    // 获取服务器全称
  getFullMQTT:function(server, port){
    return server + ":" + port.toString() + "/mqtt"
    }
})