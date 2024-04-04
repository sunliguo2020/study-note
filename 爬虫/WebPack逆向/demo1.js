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
    // n为加载器，0下标，模块是数组
    n(0)
}([
    function(){
        console.log('12345')
    },
    function(){
        console.log('模块2')
    }
])