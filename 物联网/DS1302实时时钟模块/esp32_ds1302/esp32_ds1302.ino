#include <WiFi.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

const char* ssid = "ruizhixinxi";
const char* password = "ruizhi2016";

const int CE_PIN = 5;
const int IO_PIN = 19;
const int SCLK_PIN = 18;

ThreeWire myWire(IO_PIN, SCLK_PIN, CE_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800;
const int daylightOffset_sec = 0;

void printTimeFromRTC() {
    RtcDateTime now = Rtc.GetDateTime();
    if (!now.IsValid()) {
        Serial.println("⚠️ RTC not connected or invalid time!");
        return;
    }
    Serial.printf("RTC时间: %04d-%02d-%02d %02d:%02d:%02d\n",
                  now.Year(), now.Month(), now.Day(),
                  now.Hour(), now.Minute(), now.Second());
}

void setRTCFromNTP() {
    Serial.print("Connecting WiFi ...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected!");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Getting NTP time ...");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("NTP failed, RTC unchanged.");
        return;
    }

    RtcDateTime ntpTime(
        timeinfo.tm_year + 1900,
        timeinfo.tm_mon + 1,
        timeinfo.tm_mday,
        timeinfo.tm_hour,
        timeinfo.tm_min,
        timeinfo.tm_sec
    );
    Rtc.SetDateTime(ntpTime);
    Serial.print("NTP time set to RTC: ");
    printTimeFromRTC();

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi disconnected");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(IO_PIN, INPUT_PULLUP);
    Rtc.Begin();
    Rtc.SetIsRunning(true);

    // 检查 RTC 是否有效，无效则尝试 NTP 同步
    if (!Rtc.GetDateTime().IsValid()) {
        Serial.println("RTC invalid, syncing from NTP...");
        setRTCFromNTP();
    } else {
        Serial.println("RTC valid.");
        printTimeFromRTC();
    }
    Serial.println("System ready.");
}

void loop() {
    printTimeFromRTC();
    delay(1000);
}