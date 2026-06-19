// AstroPet display unit: draws a pet face from the sensor data
// TFT_eSPI must be set to the GC9A01 driver in its User_Setup.h or the screen stays black
#include <TFT_eSPI.h>
#include <esp_now.h>
#include <WiFi.h>

struct Data { float lux, skyTemp, airTemp, humidity; } d;
TFT_eSPI tft = TFT_eSPI();
volatile bool fresh = false;
volatile unsigned long lastRecv = 0;
int last = -1;                       // -1 none, 0 sad, 1 happy, 2 asleep

void onRecv(const esp_now_recv_info_t *i, const uint8_t *data, int len) {
  if (len == sizeof(d)) { memcpy(&d, data, len); fresh = true; lastRecv = millis(); }
}

void draw(int mood) {                // 0 sad, 1 happy, 2 asleep
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(120, 110, 70, TFT_YELLOW);
  if (mood == 2) {                   // closed eyes
    tft.fillRect(85, 88, 22, 4, TFT_BLACK);
    tft.fillRect(133, 88, 22, 4, TFT_BLACK);
  } else {                           // open eyes
    tft.fillCircle(95, 90, 8, TFT_BLACK);
    tft.fillCircle(145, 90, 8, TFT_BLACK);
  }
  for (int x = -30; x <= 30; x++) {  // mouth: smile / frown / flat
    int y = mood == 1 ? 158-(x*x)/35 : mood == 0 ? 142+(x*x)/35 : 138;
    tft.fillCircle(120 + x, y, 3, TFT_BLACK);
  }
  tft.setTextColor(TFT_WHITE); tft.setTextSize(2);
  tft.setCursor(mood == 1 ? 66 : mood == 2 ? 60 : 54, 200);
  tft.print(mood == 1 ? "Go shoot!" : mood == 2 ? "No signal" : "Stay inside");
}

void setup() {
  tft.init(); tft.setRotation(0); tft.fillScreen(TFT_BLACK);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onRecv);
}

void loop() {
  if (lastRecv && millis() - lastRecv > 15000) {   // no packets for 15s -> sleep
    if (last != 2) { last = 2; draw(2); }
    return;
  }
  if (!fresh) return;
  fresh = false;
  // 3 checks: dark enough, clear sky (cold sky), low humidity
  int score = (d.lux >= 0 && d.lux < 10) + (d.airTemp - d.skyTemp > 10) + (d.humidity < 70);
  int mood = score >= 2;             // happy if 2 of 3 pass
  if (mood != last) { last = mood; draw(mood); }
}
