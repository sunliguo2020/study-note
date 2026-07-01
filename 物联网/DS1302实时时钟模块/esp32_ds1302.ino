//这个库最初由 Matt Sparks 编写，项目主页为：http://quadpoint.org/projects/arduino-ds1302
#include <DS1302.h>
// 依据网表文件映射
const int CE_PIN = 5;    // RST
const int IO_PIN = 19;   // DAT
const int SCLK_PIN = 18; // CLK

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void printTime() {
  Time t = rtc.time();
  Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                t.yr, t.mon, t.date, t.hr, t.min, t.sec);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  rtc.writeProtect(false);
  rtc.halt(false);

  // 第一次使用时可以取消注释并改成你要设置的时间
  Time t(2026, 7, 1, 9, 0, 3, Time::kWednesday);
  rtc.time(t);

  Serial.println("DS1302 ready");
}

void loop() {
  printTime();
  delay(1000);
}