```javascript
const crypto = require('crypto');  
  
const hash = crypto.createHash('sha256').update('Hello, world!').digest('hex');  
console.log(hash);
```

```javascript
const crypto = require('crypto');  
  
const input = 'Hello, world!';  
const hash = crypto.createHash('md5').update(input).digest('hex');  
  
console.log(hash); // 输出 MD5 哈希值
```