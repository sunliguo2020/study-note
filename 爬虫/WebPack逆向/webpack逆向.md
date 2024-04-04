### WebPack

是一个基于模块化的打包（构建）工具，它把一切视作模块。

webpack组成

一个最基本的webpack组成有两个部分：

- 自执行函数
- 模块加载器

### webpack打包简介
自执行函数

!function("形参"){"加载器";}(["模块"])

模块以数组形式存储，数组中的每个元素都是函数。

```javascript
!function(e){
    var t = {};
    //加载器 所有的模块都是从这个函数加载执行
    function n(r){
        if (t[r])
            return t[r].exports;
        var o = t[r] = {
            i:r,
            l:!1,
            exports:{}
        };
        return e[r].call(o.exports,o,o.exports,n),
        o.l = !0,
        o.exports
    }
    // n加载器，0下标，模块是数组
    n(0)
}([
    function(){
        console.log('12345')
    },
    function(){
        console.log('模块2')
    }
])
```



#### 多个JS文件打包
```javascript
(window.webpackJsonp = window.webpackJsonp || []).push([[9]])
```

window.webpackJsonp.push()接受三个参数，第一个参数是模块的ID，第二个参数是一个数组或对象，里面定义大量的函数，第三个参数是要调用的函数（可选）。

```javascript
//1.传入的参数是一个数组
var _xxx;
！function(x){
    function xxx(y){    #这个是模块加载器，这个y传入的可以是索引和对象的key，参数表示的是列表或对象的形参
        x[y].call(参数) 
    }
    _xxx = xxx;
}( [function(){console.log("第一个")},
    function(){consolelog("第二个")},
    function(){console.log("第三个")}
   ] );

//比如
_xxx(0); //执行得到的就是输出——第一个
_xxx(1);//执行得到的就是输出——第二个

//2.传入的参数是一个对象
var _xxx;
！function(x){
    function xxx(y){    #这个是模块加载器，这个y传入的可以是索引和对象的key，参数表示的是列表或对象的形参
        x[y].call(参数) 
    }
    _xxx = xxx;
}( {
    obj1:function(){console.log("第一个")},
    obj2:function(){consolelog("第二个")},
    obj3:function(){console.log("第三个")}
   } );
//因为传入的是一个对象，那想要调用对象就要指明key
_xxx("obj1")
_xxx("obj2")//和数组相比只是调用方式不同而已，原理基本一致
```



### 1.1 `webpack`数组形式

- 给需要处理业务的模块进行打包，通过下标取值。

```js
!function(e) {
    var t = {};

    // 加载器  所有的模块都是从这个函数加载 执行
    function n(r) {
        if (t[r])
            return t[r].exports;
        var o = t[r] = {
            i: r,
            l: !1,
            exports: {}
        };
        return e[r].call(o.exports, o, o.exports, n),
            o.l = !0,
            o.exports
    }

    n(0)
}
    ([
        function () {
            console.log('123456')
        },

        function () {
            console.log('模块2')
        },
    ])
```

### 1.2 `webpack`对象形式

- 给需要处理业务的模块进行打包，通过`key`取值。

```js
!function(e) {
    var t = {};
    //  所有的模块 都是从这个加载器 执行的  分发器
    function n(r) {
        if (t[r])
            return t[r].exports;
        var o = t[r] = {
            i: r,
            l: !1,
            exports: {}
        };
        return e[r].call(o.exports, o, o.exports, n),
        o.l = !0,
        o.exports
    }
   n(1)  // 对象 根据KEY 找模块
}({

        0: function () {
            console.log('我是模块1')
        },

        1: function () {
            console.log('我是模块2')
        }
    }
);
```

```js
!function (allModule) {
    // 函数加载器
    function useModule(whichModule) {
        // 利用 call 或 apply 调用函数
        allModule[whichModule].call(null, "hello world!");
    }
    // 加载并运行了下面数组中的第1个函数
    useModule(0)
}([
    // 用数组打包起来的函数列表
    function module0(param) {console.log("module0: " + param)},
    function module1(param) {console.log("module1: " + param)},
    function module2(param) {console.log("module2: " + param)},
]);
```



它有以下四个特征：

自执行函数：!function(){}()

自执行函数参数：[function a(){}, function b(){}, ...] 或 {a: function(){}, b: function(){}, ...}

函数加载器：function useModule(){}

函数加载器中有：call 或 apply 函数

### 总结（webpack逆向步骤）

- 找到这个加载器
- 找到调用模块
- 构造一个自执行方法
- 导出加密方法
- 编写自定义方法 按照流程加密
