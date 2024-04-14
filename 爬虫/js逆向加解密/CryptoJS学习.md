### 安装cryptoJS
```shell
npm install crypto-js
```
### MD5
```javascript

CryptoJS = require('crypto-js')
// 使用CryptoJS计算数字1（转换为字符串后）的MD5哈希
var numStr = "1"; // 数字1转换为字符串
var md5HashNumStr = CryptoJS.MD5(numStr).toString();
console.log(md5HashNumStr); // 输出MD5哈希值
```
### AES加密
```javascript

var CryptoJS = require("crypto-js");  
  
var v = function(data) {  
    // 假设您已经有了一个AES加密的密钥和初始化向量（IV）  
    var key = 'your-secret-key'; // 替换为您的密钥  
    var iv = CryptoJS.lib.WordArray.create('your-iv'); // 替换为您的IV，通常是一个16字节的随机值  
  
    // 使用CryptoJS进行AES加密  
    var encrypted = CryptoJS.AES.encrypt(data, key, {  
        iv: iv,  
        mode: CryptoJS.mode.CBC,  
        padding: CryptoJS.pad.Pkcs7  
    });  
  
    // 返回加密文本的十六进制表示  
    return encrypted.toString();  
};
```