#define LIGHT_STRIP_PIN 6                                       // пин, к которому подключена главная лента
#define LED_COUNT 144                                           // Количество светодиодов во всей главной ленте

#define BRAKELIGHT_RED_PIN 7                                    // пин для подключения красного цвета заднего света
#define BRAKELIGHT_GREEN_PIN 8                                  // пин для подключения зеленого цвета заднего света
#define BRAKELIGHT_BLUE_PIN 9                                   // пин для подключения синего цвета заднего света

#include "FastLED.h"                                            // Библиотека для светодиодной ленты


unsigned long lightStripDelayLastCalled;                        // переменная для замены delay() при помощи millis()

CRGB lightStripLEDs[LED_COUNT];
byte lightStripCounter;

void setup() {
  driverRunOnStartup();                                          // Стартовые функции драйвера
  FastLED.addLeds<WS2811, LIGHT_STRIP_PIN, GRB>(lightStripLEDs, LED_COUNT).setCorrection( TypicalLEDStrip ); // настройка ленты
  FastLED.setBrightness(50);
  pinMode(LIGHTS_PIN, OUTPUT);
}

void loop() {
  // Тут мы собираем данные с колеса
  
  eucCollectData();
  int lightStripSpeed = eucLightStripSpeed();                   // Берем данные про скорость подсветки
  
  if (millis() - lightStripDelayLastCalled >= eucLightStripSpeed ) { // Задержка
    lightStripDelayLastCalled = millis();                       // Заново считать время

    if (eucDeviceState() == 'accelerating') {
      lightStripAnimation();
    } else if (eucDeviceState() == 'braking') {
      lightStripAnimation();
    } else if (eucDeviceState() == 'back') {

    } else {
      lightStripAnimation();
    }
  }
}

void lightStripAnimation() {
  for (int i = 0; i < LED_COUNT; i++ ) {                        // от 0 до первой трети
    lightStripLEDs[i] = CHSV(lightStripCounter + i * 2, 255, 255);      // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  lightStripCounter++;                                        // lightStripCounter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
}

void brakeLightControl(bool state, bool lightType) {          // Функция для контроля заднего света
  if (state == true) {

  }
}