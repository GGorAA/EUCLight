#define LIGHTS_PIN 6                                            // пин, к которому подключена лента
#define LED_COUNT 144                                           // Количество светодиодов во всей ленте

#include "FastLED.h"

unsigned long lightStripDelayLastCalled;                        // переменная для замены delay() при помощи millis()

CRGB leds[LED_COUNT];
byte counter;

void setup() {
  FastLED.addLeds<WS2811, LIGHTS_PIN, GRB>(leds, LED_COUNT).setCorrection( TypicalLEDStrip ); // настройка ленты
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);  
}

void loop() {
  // Тут мы собираем данные с колеса
  int lightStripSpeed = eucLightStripSpeed()
  
  if (millis() - lightStripDelayLastCalled >= lightStripSpeed() ) {
    lightStripDelayLastCalled = millis();                       // заново считать время

    for (int i = 0; i < LED_COUNT; i++ ) {                      // от 0 до первой трети
      leds[i] = CHSV(counter + i * 2, 255, 255);                // HSV. Увеличивать HUE (цвет)
      // умножение i уменьшает шаг радуги
    }
    counter++;                                                  // counter меняется от 0 до 255 (тип данных byte)
    FastLED.show();
  }
}

void lightStripStopSignal() {
  
}