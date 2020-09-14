/*
 * Настройки
 */

// Настройки главной светодиодной ленты
constexpr uint8_t LIGHT_STRIP_PIN = 6;                          // Пин, к которому подключена главная лента
constexpr uint8_t LIGHT_STRIP_LED_COUNT = 144;                  // Количество светодиодов во всей главной ленте
constexpr uint8_t LIGHT_STRIP_BRIGHTNESS = 50;                  // Яркость ленты. Диапазон: 0 - 255
#define ORDER_GRB                                               // Порядок цветов

// Настройки стоп-сигнала
// Пины
constexpr uint8_t BRAKELIGHT_PIN = 5;                           // Пин подключения адресной ленты для стоп-сигнала
// Свет
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_ON = 100;               // Яркость включенного стоп-сигнала. Диапазон: 0 - 255
constexpr uint8_t BRAKELIGHT_BRIGTNESS_IDLE = 20;               // Яркость бездейвствующего стоп-сигнала. Диапазон: 0 - 255
// Анимации
constexpr uint8_t BRAKELIGHT_ANIMATION_SPEED_ON = 0;            // Скорость анимации включения стоп-сигнала. Измеряеться в миллисекундах
constexpr uint8_t BRAKELIGHT_ANIMATION_SPEED_IDLE = 500;        // Скорость анимации выключения стоп-сигнала. Измеряеться в миллисекундах
// Другое
constexpr uint8_t BRAKELIGHT_STRIP_LEDCOUNT = BRAKELIGHT_MATRIX_WIDTH * BRAKELIGHT_MATRIX_WIDTH // Количество светодиодов в каждом отрезке. Пишеться в порядке сверху-вниз
constexpr uint8_t BRAKELIGHT_MATRIX_HEIGHT = 3;                 // Высота "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_WIDTH = 8;                  // Ширина "матрицы" стоп-сигнала


#include "microLED.h"                                           // Библиотека для адресных светодиодных лент
#include "lightsControl.h"                                      // Файл для функций ленты
#include "MorsDuino.h"                                          // Библиотека для кода морзе

unsigned long lightStripDelayLastCalled;                        // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;                     // Переменная для замены delay() при помощи millis() в стоп-сигнале

LEDdata lightStripLEDs[LIGHT_STRIP_LED_COUNT];       
LEDdata brakeLightLEDs[brakeLightLEDCount];                       

microLED brakeLight(
  brakeLightLEDs,
  BRAKELIGHT_PIN,
  BRAKELIGHT_MATRIX_WIDTH,
  BRAKELIGHT_MATRIX_HEIGHT,
  ZIGZAG,
  LEFT_TOP,
  DIR_RIGHT);                                                   // Обьект стоп-сигнала
microLED mainLightStrip(
  lightStripLEDs,
  LIGHT_STRIP_LED_COUNT,
  LIGHT_STRIP_PIN);                                             // Обьект главной светодиодной ленты

MorsDuino arduinoLED(LED_BUILTIN);

void setup() {
  // Настройка пинов
  pinMode(LIGHT_STRIP_PIN, OUTPUT);
  
  driverRunOnStartup();                                         // Стартовые функции драйвера

  mainLightStrip.setBrightness(LIGHT_STRIP_BRIGHTNESS);         // Стартовая яркость главной ленты
  brakeLight.setBrightness(BRAKELIGHT_BRIGHTNESS_IDLE);         // Стартовая яркость стоп-сигнала
  mainLightStrip.show();                                        // Применить изменения
  brakeLight.show();                                            // Применить изменения
}

void loop() {
  // Тут мы собираем данные с колеса
  
  eucCollectData();
  int lightStripSpeed = eucLightStripSpeed();                     // Берем данные про скорость подсветки
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

