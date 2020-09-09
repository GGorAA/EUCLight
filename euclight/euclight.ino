// Настройки

// Настройки главной светодиодной ленты
#define LIGHT_STRIP_PIN 6                                       // Пин, к которому подключена главная лента
#define LIGHT_STRIP_LED_COUNT 144                               // Количество светодиодов во всей главной ленте
#define LIGHT_STRIP_BRIGHTNESS 50                               // Яркость ленты. Диапазон: 0 - 255
#define ORDER_GRB                                               // Порядок цветов
#define COLOR_DEBTH                                             // Глубина цвета. НАЗВАНИЕ НЕ ТРОГАТЬ, ТАК НАДО

//Настройки стоп-сигнала
// Пины
#define BRAKELIGHT_RED_PIN 9                                    // Пин для подключения красного цвета стоп-сигнала
#define BRAKELIGHT_GREEN_PIN 10                                 // Пин для подключения зеленого цвета стоп-сигнала
#define BRAKELIGHT_BLUE_PIN 11                                  // Пин для подключения синего цвета стоп-сигнала
// Свет
#define BRAKELIGHT_BRIGHTNESS 100                               // Яркость стоп-сигнала. Диапазон: 0 - 255
// Анимации
#define BRAKELIGHT_ANIMATION_SPEED_ON 0                         // Скорость анимации включения стоп-сигнала. Измеряеться в миллисекундах
#define BRAKELIGHT_ANIMATION_SPEED_OFF 500                      // Скорость анимации выключения стоп-сигнала. Измеряеться в миллисекундах


#include "microLED.h"                                           // Библиотека для адресной светодиодной ленты
#include "GyverRGB.h"                                           // Библиотека для светодиодов и обычных RGB лент

unsigned long lightStripDelayLastCalled;                        // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;                     // Переменная для замены delay() при помощи millis() в стоп-сигнале

LEDdata lightStripLEDs[LED_COUNT];                              
GRGB brakeLight(BRAKELIGHT_RED_PIN, BRAKELIGHT_GREEN_PIN, BRAKELIGHT_BLUE_PIN); // Обьект стоп-сигнала
microLED mainLightStrip(lightStripLEDs, LIGHT_STRIP_LED_COUNT, LIGHT_STRIP_PIN); // Обьект главной светодиодной ленты

void setup() {
  driverRunOnStartup(brakeLightBrightness);                                          // Стартовые функции драйвера
  mainLightStrip.setBrightness(mainLightStripBrightness)
  brakeLight.setBrightness()
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

    if (eucDeviceState() == 'accelerating') {                   // Если моноколесо ускоряеться
      brakeLightControl(false);                                 // Выключить стоп-сигнал
      mainLightStripAnimation();                                // Анимация главной светодиодной ленты
    } else if (eucDeviceState() == 'braking') {
      brakeLightControl(true, 1);
      mainLightStripAnimation();
    } else if (eucDeviceState() == 'back') {
      brakeLightControl(true, 2);
    } else {
      brakeLightControl(false);
      mainLightStripAnimation();
    }
  }
}
