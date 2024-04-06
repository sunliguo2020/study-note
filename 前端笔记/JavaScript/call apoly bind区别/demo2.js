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