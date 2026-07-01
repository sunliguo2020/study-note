#include <ThreeWire.h>
#include <RtcDS1302.h>

const int CE_PIN = 5;    // RST
const int IO_PIN = 19;   // DAT
const int SCLK_PIN = 18; // CLK

ThreeWire myWire(IO_PIN, SCLK_PIN, CE_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

void printTime() {
    RtcDateTime now = Rtc.GetDateTime();
    Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                  now.Year(), now.Month(), now.Day(),
                  now.Hour(), now.Minute(), now.Second());
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // 开启内部上拉（如果已外接4.7k电阻，这行可保留或删除）
    pinMode(IO_PIN, INPUT_PULLUP);

    Rtc.Begin();
    Rtc.SetIsRunning(true);

    // ============================================================
    // 重点！取消下面这段注释，并将时间改为你当前的北京时间
    // 只需要运行一次，之后可以重新注释掉再上传，以防每次重启都重置时间
    // ============================================================
    // RtcDateTime setTime(2026, 7, 1, 9, 22, 0);  // 年,月,日,时,分,秒
    // Rtc.SetDateTime(setTime);
    // ============================================================

    Serial.println("DS1302 ready");
}

void loop() {
    printTime();
    delay(1000);
}