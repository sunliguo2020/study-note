## JavaScript进阶

### 一、变量提升

### 逗号运算符

 **逗号**（**`,`**）运算符对它的每个操作数从左到右求值，并返回最后一个操作数的值。 

### 二、闭包函数

```javascript
let name = '周杰伦'
function chi(){
    name = '吃';
}
chi();
console.log(name)
```

### 三、JS中的各种操作

#### 3.1 定时器

```javascript 
setTimeout(function(){},2000);
```

无限debug：

- 最好的解决方案：在行号的位置，右键=>never pasuse here,然后释放断点
- 置空法（hook的逻辑），可以对无限debuger的入口进行置空。也可以对setTimeout(),setInterval进行置空。
- hook.

```javascript
setInterval(function(){},200)
```

#### 3.2 时间

```javascript
var now = new Date();//当前时间

console.log(now.getTime())
var n = Date.now();//时间戳
//时间格式化
var d = new Date();
var year = d.getFullYear();
var month = d.getMonth();
var day = d.getDate();
var hour = d.getHours();

var result = `${year}-${month}-${day}`
```

#### 3.3 eval函数

```javascript
var code = '1+1'
eval(code);
```



#### Math

```javascript
console.log(Math.random()); //随机数
```



### 3.5神奇的 window



#### 3.7 ES6中的箭头函数

```javascript

var mm = function(a,b){return a+b}
//es6 可以简化
var mm = (a,b) =>{
    return a+b
}
//注意事项
//1、如果只有一个函数，小括号可以省略
var fn = a =>{
    console.log('这是一个函数参数是：',a)
}
//2、this的逻辑和普通的function不一样

//ES6新特性
var name = 'qiaofu'
var age = 18;
var password = 123456;

var chi = function(){
    console.log('吃饭睡觉，打豆豆！')
}

var person = {
    //username :username,
    // age:age,
    // password:password,
    //chi:chi,
    //如果属性名和一个变量名完全一样，并且，你需要用该变量来表示该属性
    username,//username = username
    age,
    password,
    chi,
    he:function(){
        console.log('我要喝东西');
    },
    la(){
        console.log('我要拉东西');
    }
}
 var obj = {
     "name":'汪峰',
     age:18,
     wife:{
         name:'子怡'，
         age:28
     }
 }
 
 var age = obj.age;
var wife = obj.wife;
var name = obj.name;

//前端解构
var {age,wife,name} = obj;

```

#### 三元表达式

一个条件后跟一个问号（`?`），如果条件为[真值](https://developer.mozilla.org/zh-CN/docs/Glossary/Truthy)，则执行冒号（`:`）前的表达式；若条件为[假值](https://developer.mozilla.org/zh-CN/docs/Glossary/Falsy)，则执行最后的表达式。

```javascript
condition ? exprIfTrue : exprIfFalse
```

