#define LIGHT_STRIP_PIN 6                                       // Пин, к которому подключена главная лента
#define LED_COUNT 144                                           // Количество светодиодов во всей главной ленте
#define LIGHT_STRIP_BRIGHTNESS 50                               // Яркость ленты

#define BRAKELIGHT_RED_PIN 9                                    // Пин для подключения красного цвета заднего света
#define BRAKELIGHT_GREEN_PIN 10                                 // Пин для подключения зеленого цвета заднего света
#define BRAKELIGHT_BLUE_PIN 11                                  // Пин для подключения синего цвета заднего света

#include "FastLED.h"                                            // Библиотека для светодиодной ленты


unsigned long lightStripDelayLastCalled;                        // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;                     // Переменная для замены delay() при помощи millis() в заднем свете

CRGB lightStripLEDs[LED_COUNT];
byte lightStripCounter;

void setup() {
  driverRunOnStartup();                                          // Стартовые функции драйвера
  FastLED.addLeds<WS2811, LIGHT_STRIP_PIN, GRB>(lightStripLEDs, LED_COUNT).setCorrection( TypicalLEDStrip ); // настройка ленты
  FastLED.setBrightness(LIGHT_STRIP_BRIGHTNESS);
  // Настройка пинов
  pinMode(LIGHT_STRIP_PIN, OUTPUT);
  pinMode(BRAKELIGHT_RED_PIN, OUTPUT);
  pinMode(BRAKELIGHT_GREEN_PIN, OUTPUT);
  pinMode(BRAKELIGHT_BLUE_PIN, OUTPUT);
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
  for (int i = 0; i < LED_COUNT; i++ ) {                        // От 0 до первой трети
    lightStripLEDs[i] = CHSV(lightStripCounter + i * 2, 255, 255);      // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  lightStripCounter++;                                        // lightStripCounter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
}

void brakeLightControl(bool state, int lightType = 0) {          // Функция для контроля заднего света
  if (state == true) {
    if (lightType == 0) {
      digitalWrite(BRAKELIGHT_RED_PIN, HIGH);
    } else if (lightType == 1) {
      digitalWrite(BRAKELIGHT_RED_PIN, HIGH);
      digitalWrite(BRAKELIGHT_GREEN_PIN, HIGH);
      digitalWrite(BRAKELIGHT_BLUE_PIN, HIGH);
    }
  } else if (state == false) {
    if (lightType == 0) {
      digitalWrite(BRAKELIGHT_RED_PIN, LOW);
    } else if (lightType == 1) {
      for (int i = 100; 1 <= 100; i--) {
        int duty = map(i, 0, 100, 0, 255);
        if(millis() - brakeLightOffDelayLastCalled >= 20) {
          brakeLightOffDelayLastCalled = millis();

          analogWrite(BRAKELIGHT_RED_PIN, duty);
          analogWrite(BRAKELIGHT_GREEN_PIN, duty);
          analogWrite(BRAKELIGHT_BLUE_PIN, duty);
        }
      }
      digitalWrite(BRAKELIGHT_GREEN_PIN, LOW);
      digitalWrite(BRAKELIGHT_BLUE_PIN, LOW);
    }
  }
}