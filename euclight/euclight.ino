/*
 * Настройки
 */

// Настройки главной светодиодной ленты
constexpr uint8_t LIGHT_STRIP_PIN = 6;                          // Пин, к которому подключена главная лента
constexpr uint8_t LIGHT_STRIP_LED_COUNT = 144;                  // Количество светодиодов во всей главной ленте
constexpr uint8_t LIGHT_STRIP_BRIGHTNESS_ON = 50;               // Яркость ленты. Диапазон: 0 - 255
#define ORDER_GRB                                               // Порядок цветов

// Настройки стоп-сигнала
// Пины
constexpr uint8_t BRAKELIGHT_RED_PIN = 9;                       // Пин для подключения красного цвета стоп-сигнала
constexpr uint8_t BRAKELIGHT_GREEN_PIN = 10;                    // Пин для подключения зеленого цвета стоп-сигнала
constexpr uint8_t BRAKELIGHT_BLUE_PIN = 11;                     // Пин для подключения синего цвета стоп-сигнала
// Свет
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_ON = 100;               // Яркость включенного стоп-сигнала. Диапазон: 0 - 255
constexpr uint8_t BRAKELIGHT_BRIGTNESS_IDLE = 20;
// Анимации
//constexpr uint8_t BRAKELIGHT_ANIMATION_SPEED_ON = 0;            // Скорость анимации включения стоп-сигнала. Измеряеться в миллисекундах
//constexpr uint8_t BRAKELIGHT_ANIMATION_SPEED_IDLE = 500;        // Скорость анимации выключения стоп-сигнала. Измеряеться в миллисекундах


#include "microLED.h"                                           // Библиотека для адресной светодиодной ленты
#include "GyverRGB.h"                                           // Библиотека для светодиодов и обычных RGB лент
#include "lightsControl.h"                                      // Файл для функций ленты
#include "MorsDuino.h"                                          // Библиотека для кода морзе

unsigned long lightStripDelayLastCalled;                        // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;                     // Переменная для замены delay() при помощи millis() в стоп-сигнале

LEDdata lightStripLEDs[LIGHT_STRIP_LED_COUNT];                              
GRGB brakeLight(BRAKELIGHT_RED_PIN, BRAKELIGHT_GREEN_PIN, BRAKELIGHT_BLUE_PIN); // Обьект стоп-сигнала
microLED mainLightStrip(lightStripLEDs, LIGHT_STRIP_LED_COUNT, LIGHT_STRIP_PIN); // Обьект главной светодиодной ленты
MorsDuino arduinoLED(13);

void setup() {
  driverRunOnStartup();                                          // Стартовые функции драйвера
  mainLightStrip.setBrightness(LIGHT_STRIP_BRIGHTNESS_ON);
  brakeLight.setBrightness(BRAKELIGHT_BRIGHTNESS_ON);
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
  controlLights();
}

void controlLights() {
  if (millis() - lightStripDelayLastCalled >= eucLightStripSpeed ) { // Задержка
    lightStripDelayLastCalled = millis();                         // Заново считать время

    switch (eucDeviceState()) {                                   // Если моноколесо ускоряеться
      case 1:
        brakeLightControl(false);                                 // Выключить стоп-сигнал
        mainLightStripAnimation(1);                               // Анимация главной светодиодной ленты
        break;
      case 2:
        brakeLightControl(true, 1);
        mainLightStripAnimation(1);
      case 3:
        brakeLightControl(true, 2);
        mainLightStripAnimation(2);
      case 4:

      default:
        break;
    }
  }
}

