### 说一下call apply bind 的区别

#### 共同点：功能一致

- 可以改变this指向
- 语法：函数.call() 函数.apply() 函数.bind()

#### 区别：

- 1、call apply可以立即执行。bind不会立即执行。
- 2、

函数.call(arg1,arg2,)

基于call执行函数，第一个参数赋值给this