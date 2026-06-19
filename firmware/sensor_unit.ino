// AstroPet sensor unit: reads the sky and broadcasts over ESP-NOW every 5s
#include <Wire.h>
#include <Adafruit_TSL2591.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_BME280.h>
#include <esp_now.h>
#include <WiFi.h>

struct Data { float lux, skyTemp, airTemp, humidity; } d;
uint8_t peer[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
Adafruit_MLX90614 mlx;
Adafruit_BME280 bme;
unsigned long last = 0;

void setup() {
  Wire.begin(8, 9);                 // SDA 8, SCL 9
  tsl.begin(); mlx.begin(); bme.begin(0x76);   // try 0x77 if bme not found
  tsl.setGain(TSL2591_GAIN_HIGH);              // more sensitive in the dark
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_peer_info_t p = {};
  memcpy(p.peer_addr, peer, 6);
  esp_now_add_peer(&p);
}

void loop() {
  if (millis() - last < 5000) return;
  last = millis();
  sensors_event_t e; tsl.getEvent(&e);
  d.lux = e.light;
  d.skyTemp = mlx.readObjectTempC();
  d.airTemp = mlx.readAmbientTempC();
  d.humidity = bme.readHumidity();
  esp_now_send(peer, (uint8_t*)&d, sizeof(d));
}
