#define LIGHTS_PIN 6                                            // пин, к которому подключена лента
#define LED_COUNT 144                                           // Количество светодиодов во всей ленте

#include "FastLED.h"                                            // Библиотека для светодиодной ленты


unsigned long lightStripDelayLastCalled;                        // переменная для замены delay() при помощи millis()

CRGB leds[LED_COUNT];
byte lightStripCounter;

void setup() {
  driverRunOnStartup();                                          // Стартовые функции драйвера
  FastLED.addLeds<WS2811, LIGHTS_PIN, GRB>(leds, LED_COUNT).setCorrection( TypicalLEDStrip ); // настройка ленты
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);
}

void loop() {
  // Тут мы собираем данные с колеса
  
  eucCollectData()
  int lightStripSpeed = eucLightStripSpeed();                   // Берем данные про скорость подсветки
  
  if (millis() - lightStripDelayLastCalled >= lightStripSpeed ) { // Задержка
    lightStripDelayLastCalled = millis();                       // Заново считать время

    switch (eucDeviceState()) {
      case 'a':
        lightSpeedNormal();
        break;
      case 'b':
        lightStripWithStopSignal();
        break;
      default:
        lightSpeedNormal();
        break;
    }
  }
}

void lightSpeedNormal() {
  for (int i = 0; i < LED_COUNT; i++ ) {                        // от 0 до первой трети
      leds[i] = CHSV(lightStripCounter + i * 2, 255, 255);      // HSV. Увеличивать HUE (цвет)
      // умножение i уменьшает шаг радуги
    }
    lightStripCounter++;                                        // lightStripCounter меняется от 0 до 255 (тип данных byte)
    FastLED.show();
}

void lightStripWithStopSignal() {

}