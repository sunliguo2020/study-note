#include <WiFi.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// ---------- WiFi 配置 ----------
const char* ssid = "ruizhixinxi";
const char* password = "ruizhi2016";

// ---------- DS1302 引脚 ----------
const int CE_PIN = 5;    // RST
const int IO_PIN = 19;   // DAT
const int SCLK_PIN = 18; // CLK

ThreeWire myWire(IO_PIN, SCLK_PIN, CE_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

// ---------- NTP 时间服务器 ----------
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800;   // 中国时区 UTC+8 (8*3600)
const int   daylightOffset_sec = 0;  // 无夏令时

void printTimeFromRTC() {
    RtcDateTime now = Rtc.GetDateTime();
    Serial.printf("RTC时间: %04d-%02d-%02d %02d:%02d:%02d\n",
                  now.Year(), now.Month(), now.Day(),
                  now.Hour(), now.Minute(), now.Second());
}

void setRTCFromNTP() {
    Serial.print("正在连接 WiFi ...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" 已连接！");

    // 配置 NTP
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("正在获取 NTP 时间 ...");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("获取 NTP 时间失败，将保持 RTC 原有时间");
        return;
    }

    // 将 tm 结构转换为 RtcDateTime 格式（年份需要加 1900，月份加 1）
    RtcDateTime ntpTime(
        timeinfo.tm_year + 1900,
        timeinfo.tm_mon + 1,
        timeinfo.tm_mday,
        timeinfo.tm_hour,
        timeinfo.tm_min,
        timeinfo.tm_sec
    );

    // 写入 DS1302
    Rtc.SetDateTime(ntpTime);
    Serial.print("NTP 时间已同步至 RTC: ");
    printTimeFromRTC();

    // 断开 WiFi 以省电（可选）
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi 已断开");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // 初始化 DS1302
    pinMode(IO_PIN, INPUT_PULLUP);  // 如果外接上拉电阻，此行可保留或删除
    Rtc.Begin();
    Rtc.SetIsRunning(true);

    // 从 NTP 同步时间（首次运行或需要校准时执行）
    setRTCFromNTP();

    Serial.println("系统就绪，开始每秒打印 RTC 时间：");
}

void loop() {
    printTimeFromRTC();
    delay(1000);
}