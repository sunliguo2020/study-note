const jsdom = require("jsdom");
const {JSDOM} = jsdom;

const html = `<!DOCTYPE html><p>Hello world</p>`;
const dom = new JSDOM(html, {
    url: "https://www.toutiao.com",
    referrer: "https://example.com/",
    contentType: "text/html"
});

document = dom.window.document;

window = global;
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
});

location = window.location;

XMLHttpRequest = function () {
    return {
        open:function(){},
        setRequestHeader:function(){},
        send:function(){},
    }
}


function func(arg) {
    var xhr = new XMLHttpRequest();
    xhr.open('POST', "/test/", true);
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset-UTF-8');
    xhr.send('n1=1;n2=2;');

    return arg + "666" + location.href + window.navigator.userAgent;
}