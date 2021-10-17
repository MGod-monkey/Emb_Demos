//index.js
Component({
  /**
   * 组件的属性列表
   */
  properties: {
    propArray: {
      type: Array,
    }
  },
  /**
   * 组件的初始数据
   */
  data: {
    selectShow: false,//初始option不显示
    selectText: "请选择你要播放的MP3",//初始内容
  },
  /**
   * 组件的方法列表
   */
  methods: {
    //option的显示与否
    selectToggle: function () {
      var nowShow = this.data.selectShow;//获取当前option显示的状态

      this.setData({
        selectShow: !nowShow
      })
    },
    //设置内容
    setText: function (e) {
      var nowData = this.properties.propArray;//当前option的数据是引入组件的页面传过来的，所以这里获取数据只有通过this.properties
      var nowIdx = e.currentTarget.dataset.index;//当前点击的索引
      var nowName = nowData[nowIdx]['name']//当前点击的内容
      var nowUrl = nowData[nowIdx]['url'] 
      //再次执行动画，注意这里一定，一定，一定是this.animation来使用动画
      this.setData({
        selectShow: false,
        selectText: "当前选择: " + nowName,
      })
      // this.triggerEvent('id', nowIdx)
      // this.triggerEvent('select', nowName)
      this.triggerEvent('url', nowUrl)
    }
  }
})