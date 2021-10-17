// app.js
App({
  // onLaunch() {
  //   // 登录
  //   wx.login({
  //     success: res => {
  //       // 发送 res.code 到后台换取 openId, sessionKey, unionId
  //     }
  //   })
  // },
  globalData: {
    userInfo: null,
    client: null,
    filePaths: ['',''],
    serverIP: '120.25.224.86',
    MQTTServer: "broker-cn.emqx.io",
    MQTTPort: "8083",
    topic: "/mgodmonkey",
    deviceIP: "",
    deviceIsFree: true,
    mqttStatusCode: 0,  //状态码：-1：错误 0：正在连接 1：连接成功
    topicStatusCode: 0,
    email: "1781434602@qq.com",
    author: "1900200327吴佩钦",
    github: "等待作者发布",
    version: "1.2"
  }
})
