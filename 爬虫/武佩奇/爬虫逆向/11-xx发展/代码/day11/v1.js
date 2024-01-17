function func(arg) {
    return arg + '666';
}

var name = process.argv[2];
var res = func(name);
console.log(res);
