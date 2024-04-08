### 安装jsdom
```
npm i jsdom 
//全局安装
npm install jsodm -g 
npm install -g node-gyp
npm install -g canvas
```
### 查看npm安装目录
```
npm root -g 
```
### 配置环境变量


```javascript

const jsdom = require("jsdom");
const { JSDOM } = jsdom;
const dom = new JSDOM(`<!DOCTYPE html><p>Hello world</p>`);

document = dom.window.document;
window  = global;

Object.assign(global, {
    location: {
        hash: "",
        host: "user.qunar.com",
        hostname: "user.qunar.com",
        href: "https://user.qunar.com/passport/login.jsp",
        origin: "https://user.qunar.com",
        pathname: "/",
        port: "",
        protocol: "https:",
        search: "",
    },
    navigator: {
        appCodeName: "Mozilla",
        appName: "Netscape",
        appVersion: "5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36",
        cookieEnabled: true,
        deviceMemory: 8,
        doNotTrack: null,
        hardwareConcurrency: 4,
        language: "zh-CN",
        languages: ["zh-CN", "zh"],
        maxTouchPoints: 0,
        onLine: true,
        platform: "MacIntel",
        product: "Gecko",
        productSub: "20030107",
        userAgent: "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36",
        vendor: "Google Inc.",
        vendorSub: "",
        webdriver: false
    }
})

console.log(dom.window.document.querySelector("p").textContent); // "Hello world"
```

