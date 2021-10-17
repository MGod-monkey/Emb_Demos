// pages/setcolor/setcolor.js
const app = getApp();
Page({
  data: {
    rgb: 'rgb(0,229,255)',//初始值
    rgbList: [0,229,255],
    tonalrgb: 'rgb(255,26,0)',
    tonalrgbList: [255,26,0],
    speed: 90,
    brightness: 36,
    pick: false,
    switch1: true,
    switch2: true,
    switch3: true,
    switch4: true
  },
  onLoad:function() {
    this.sendRGB()
  },
  // 设置的开关
  showModal(e) {
    this.setData({
      modalName: e.currentTarget.dataset.target
    })
  },
  hideModal(e) {
    this.setData({
      modalName: null
    })
  },
    // 显示取色器
  toPick: function () {
    this.setData({
      pick: true
    })
  },
    //获取反色调数值
    getTonal:function(color){
      var rgb = color.split(',');
      var R = parseInt(rgb[0].split('(')[1]);
      var G = parseInt(rgb[1]);
      var B = parseInt(rgb[2].split(')')[0]);

      R = 255 - R;
      G = 255 - G;
      B = 255 - B;
      return "rgb(" + R + "," + G + "," + B + ")"
    },
    //文字转列表
    text2List:function(color) {
      var rgb = color.split(',');
      var R = parseInt(rgb[0].split('(')[1]);
      var G = parseInt(rgb[1]);
      var B = parseInt(rgb[2].split(')')[0]);
      return [R, G, B]
    },
    //列表转文字
    list2text:function(list) {
      return "rgb(" + list[0] + "," + list[1] + "," + list[2] + ")"
    },
    //取色结果回调
    pickColor(e) {
      var rgb = e.detail.color;
      var tonalrgb = this.getTonal(rgb);
      this.setData({
        rgb: rgb,
        rgbList: this.text2List(rgb),
        tonalrgb: tonalrgb,
        tonalrgbList: this.text2List(tonalrgb)
      })
      if (!this.data.switch2) {this.sendRGB()}
    },
    //更改颜色值
    changeColor:function(e){
      var value = parseInt(e.detail.value)
      var id = e.target.id
      var rgbList = this.data.rgbList
      var tonalrgbList = this.data.tonalrgbList
      if (value > 255 || value < 0||isNaN(value))  value = value>255?255:0
      if (id == "red") rgbList[0] = value
      else if (id == "green") rgbList[1] = value
      else if (id == "blue")  rgbList[2] = value
      else if (id == "tonalred")  tonalrgbList[0] = value
      else if (id == "tonalgreen") tonalrgbList[1] = value
      else if (id == "tonalblue")  tonalrgbList[2] = value
      if (id == "red"||id == "blue"||id == "green"){
         var rgb = this.list2text(rgbList)
         var tonalrgb = this.getTonal(rgb)
         tonalrgbList = this.text2List(tonalrgb)}
      else if (id == "tonalred"||id == "tonalgreen"||id == "tonalblue"){
        var tonalrgb = this.list2text(tonalrgbList)
        var rgb = this.getTonal(tonalrgb)
        rgbList = this.list2text(rgb)
      }
      this.setData({
        rgb: rgb,
        rgbList: rgbList,
        tonalrgb: tonalrgb,
        tonalrgbList: tonalrgbList
      })
      // if (value == 0 || value == 255 || value == NaN)  return value
    },
  onChange(e){
    switch (e.target.id) {
      case 'switch1':
        this.setData({switch1:e.detail.value});break;
      case 'switch2':
        this.setData({switch2:e.detail.value,switch3:true});break;
      case 'switch3':
        this.setData({switch3:e.detail.value});break;
      default:
        this.setData({switch4:e.detail.value});break;
    }
    this.sendRGB()
  },
  setSpeed:function(e) {
    this.setData({speed: e.detail.value})
    this.sendRGB()
  },
  setBrightness:function(e){
    this.setData({brightness: e.detail.value})
    this.sendRGB()
  },
  // 发送更改RGB灯指令
  // 格式：color_r, color_g, color_b, brightness, speed, cmd
  // 示例：64,245,68,64,500,3
  // cmd: 0关闭 1开启 2暂停 3静态颜色 4闪烁 5呼吸
  // 6呼吸彩虹灯 7无呼吸彩虹灯
  sendRGB:function(){
    if (!app.globalData.client.connected) {
        wx.showToast({
          title: '服务器未连接',
          icon: 'error',
          mask: true,
          duration: 1000
        })
        return;
    }
    if (app.globalData.deviceIP == '') {
        wx.showToast({
          title: '设备未连接',
          icon: 'error',
          mask: true,
          duration: 1500
        })
        return;
    }
    if (this.data.switch1) var color = this.data.rgbList
    else var color = this.data.tonalrgbList
    var speed = 2000 - 22 * (this.data.speed - 10)

    if (this.data.switch2 && this.data.switch4) { // 呼吸彩虹灯
      var msg = '128,128,128,' + this.data.brightness + ',' 
            + speed + ',6'}
    else if (this.data.switch2 && !this.data.switch4) {  // 闪烁彩虹灯
      var msg = '128,128,128,' + this.data.brightness + ',' 
              + speed + ',7'}
    else if (!this.data.switch2 && !this.data.switch3) {  // 静止固定灯
      var msg = color[0] + ',' + color[1] + ',' + color[2] + ',' + this.data.brightness + ','   + speed + ',3'}
    else if (!this.data.switch2 && this.data.switch3 && !this.data.switch4) {  // 闪烁灯
      var msg = color[0] + ',' + color[1] + ',' + color[2] + ',' + this.data.brightness + ',' 
      + speed + ',4'}
    else if (!this.data.switch2 && this.data.switch3 && this.data.switch4) {  // 呼吸灯
      var msg = color[0] + ',' + color[1] + ',' + color[2] + ',' + this.data.brightness + ',' 
      + speed + ',5'}
    else {
      console.log('指令错误！请检查');return ;
    }
    const topic = app.globalData.topic + '/rgb'
    app.globalData.client.publish(topic, msg, {
      qos:0, rein: false
    })
  }
})