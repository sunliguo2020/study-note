var obj = {
    'username':'sunliguo'
}
//hook的写法
Object.defineProperty(obj,"username",{

    get(){
        // 对应的取值操作
        console.log('你从obj中读取username')
        return '你好'
    }
})

console.log(obj.username)