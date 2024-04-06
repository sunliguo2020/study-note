
function method(a,b){
    console.log(this,a,b)
    return a+b
}

// method.call({},1,3)
console.log(method.call({},2,3))