# 一、脚手架安装

```
npm insatall @vue/cli -g 
```

检验版本

```
C:\Users\sunliguo>vue -V
@vue/cli 5.0.8

```
# 二、通过脚手架创建项目

## 2.1 命令行

### 2.1.1 第1种命令行

```
vue create my-vue-project
Vue CLI v5.0.8
? Please pick a preset: (Use arrow keys)
  Default ([Vue 3] babel, eslint)
  Default ([Vue 2] babel, eslint)
 >Manually select features
```

```
? Please pick a preset: Manually select features
? Check the features needed for your project: (Press <space> to select, <a> to toggle all, <i> to invert 
selection, and <enter> to proceed)
 (*) Babel
 ( ) TypeScript
 ( ) Progressive Web App (PWA) Support
 (*) Router
 ( ) Vuex
>(*) CSS Pre-processors
 (*) Linter / Formatter
 ( ) Unit Testing
 ( ) E2E Testing
```



### 2.1.2 第2种 图形

```
vue ui
```

# 三、项目结构和介绍

&gt;node_modules	项目的各种依赖

&gt;public					存放静态资源

&gt;src							存放各种vue文件

​	&gt;assets				存放各种静态文件不，比如图片、字体

​	&gt;components	 公共组件

​	&gt;router				vue-router路由文件

​	&gt;views					存放各种页面，如：home、user

​	&gt;App.vue			项目主组件，所有的页面都是在App.vue下切换

​	&gt;main.js				入口文件，主要作用是初始化vue实例

basel.config.js	工具链

package.json 模块的基本信息项目开发所需的模块

package-lock.json 记录当前状态下实际安装的各个npm package的具体来源和版本号

