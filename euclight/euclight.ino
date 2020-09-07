#define DEBUG_ENABLED true // запуск режима отладки. 
#define LIGHTS_PIN 6 // пин, к которому подключена лента
#define LED_COUNT 144 // Количество светодиодов во всей ленте

#include "FastLED.h"
#include <EucInterface.h>

CRGB leds[LED_COUNT];
byte counter;

void setup() {
  if (DEBUG_ENABLED == true) {
    setupSerial();
  }
  FastLED.addLeds<WS2811, LIGHTS_PIN, GRB>(leds, LED_COUNT).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < LED_COUNT; i++ ) {         // от 0 до первой трети
    leds[i] = CHSV(counter + i * 2, 255, 255);  // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
  delay(5);         // скорость движения радуги
}