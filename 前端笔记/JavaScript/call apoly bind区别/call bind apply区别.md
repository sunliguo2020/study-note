### 说一下call apply bind 的区别

#### 共同点：功能一致

- 可以改变this指向
- 语法：函数.call() 函数.apply() 函数.bind()

#### 区别：

- 1、call apply可以立即执行。bind不会立即执行。
- 2、

函数.call(arg1,arg2,)

基于call执行函数，第一个参数赋值给this

```javascript
    function fn(num1,num2){
    console.log(this)
    return num1+num2;
}

let obj = {name:'马路'}
// 1、改变fn中this的指向
// 2、call可以让函数调用
// 3、返回函数调用的结果

let res =fn.call(obj,1,2)
console.log(res)
```