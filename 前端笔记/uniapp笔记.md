# uniapp

# 一、开发环境

## 1.1 HBuilder

技巧一：创建自定义模板快速创建vue3页面

新建uni-app页面->自定义模板->新建文本文件

```vue
<template>
	<view>
	</view>
</template>

<script setup>

</script>

<style lang="scss" scoped>

</style>


```



# 二、常见组件

每个组件包括一下几个部分：以组件名称为标记的开始标签和结束标签、组件内容、组件属性和组件属性值。

> 注意：所有组件与属性名都是小写，单词之间以连字符-连接。

下面是一个基本组件的实例，在一个vue页面的根`<view>`组件下插入一个`<button>`组件。给这个组件的内容区写上文字“按钮”，同时给这个组件设置了一个属性“size”，并且“size”属性的值设为了“mini”。

```vue
<template>
	<view>
		<button size="mini" :disabled="false" hover-start-time=20 >按钮</button>
	</view>
</template>
```

#### 在组件中使用script的data变量

组件中可以使用script的data中定义的变量，但组件的属性中使用和内容区使用的用法不一样。

- 在text内容区使用时，使用两个花括号来包裹，如下面的`buttonText`
- 在属性值中使用时，属性名的前面要加冒号前缀

下面的button组件示例，等价于上一个的示例。只不过静态内容改成动态js。

```vue
<template>
	<view>
		<button size="mini" :disabled="buttondisble" hover-start-time=20 >{{buttonText}}</button>
	</view>
</template>
<script>
	export default {
		data() {
			return {
				"buttonText":"按钮",
				"buttondisble":false
			}
		}
	}
</script>
```

#### 组件的事件

每个组件都有“事件”。事件就是在指定的条件下触发某个js方法。

事件也是组件的属性，只不过这类属性以`@`为前缀。

事件的属性值，指向一个在script的methods里定义过的js方法，还可以给方法传参数。

下面是组件事件的示例：

- click是button组件的点击事件，在用户点击这个button时触发
- click指向了methods中定义的goto方法，并且传递了一个参数'/pages/about/about'

```html
<template>
	<view>
		<button size="mini" @click="goto('/pages/about/about')">按钮</button>
	</view>
</template>
<script>
    export default {
        methods: {
            goto(url) {
                console.log("按钮被点击了，且传入的参数是：" + url)
            }
        }
    }
</script>
```

## 2.1 内置组件

### 2.1.1 uni-app组件

#### image

<image>未设置宽高时，默认宽度为320px，高度为240px。





## 2.1 view

功能：包裹各种元素的内容，自带事件效果属性。

常用属性名：

- hover-stop-propagation
- 

## 2.2 text

文本组件，用于包裹文本。可以实现长按选择文字、连续空格、解码功能。

## 2.3 scroll-view

可滚动视图区域，用于区域滚动。

常用属性值

- scroll-x
- scroll-y
- 

## 2.4 swiper

滑块视图容器，用于制作轮播图效果。



# 三、扩展组件

### 3.1 uni-dateformat 日期格式化

基本用法：在template中使用组件

```vue
<!-- 一般用法 -->
<uni-dateformat date="2020/10/20 20:20:20"></uni-dateformat>

<!-- 不显示刚刚/马上/xx分钟前 -->
<uni-dateformat date="2020/10/20 20:20:20" :threshold="[0,0]"></uni-dateformat>
```

### 3.2 uni-load-more 加载更多

```vue
<uni-load-more status="more"></uni-load-more>
```

# 四、生命周期

## 4.1、页面周期函数

首先要从@dcloudio/uni-app中引入

```javascript
import {onReachBottom } from "@dcloudio/uni-app"	
```



### 4.1.1 onReachBottom 触底加载更多

```javascript
	import {onReachBottom } from "@dcloudio/uni-app"	
    onReachBottom(()=>{
            queryParms.pageNum++;
            if (noData.value){
                return ;
            }
            getClassList();
        })
```

### 4.1.2 onPullDownRefresh 下拉刷新

首先，在pages.json里找到当前页面的pages节点，并在style选项中开启enablePullDownRefresh,才能支持下拉刷新。

```json
{
	"pages": [ //pages数组中第一项表示应用启动页，参考：https://uniapp.dcloud.io/collocation/pages
		{
			"path": "pages/index/index",
			"style": {
				"navigationBarTitleText": "",
				"navigationStyle": "custom",
                "enablePullDownRefresh" : true, //开启下拉刷新
			}
		},
		{
			"path" : "pages/classify/classify",
			"style" : 
			{
				"navigationBarTitleText": "分类",
				"enablePullDownRefresh" : false,
				"navigationStyle": "custom"
			}
		}
        ]
}
```

```
//监听下拉刷新事件
<script setup>
onPullDownRefresh(()=>{
//下拉刷新后
})
</script>
```



### 4.1.3 onLoad 监听页面加载

其参数为上一个页面传递的数据，参数类型为Object（用于页面传参）

```javascript
import {onLoad,	} from "@dcloudio/uni-app";
onLoad((e) => {
		console.log(e);
		let {
			id = null, name = null
		} = e;
		console.log(id, name);
		queryParms.classid = id;
		uni.setNavigationBarTitle({
			title: name
		})
		getClassList();
	});
```



### 4.1.3 onShow监听页面显示

```javascript
<script setup>
//该依赖已内置不需要单独安装
import { onLoad, onShow } from "@dcloudio/uni-app";
onShow(()=>{
   console.log('onShow==')
})
</script>
```



### 底部安全区域css环境变量

env(safe-area-inset-bottom)

在common-style.scss中

```css
.safe-area-inset-bottom{
    height:env(safe-area-inset-bottom);
}
```

