// Настройки главной светодиодной ленты
#define LIGHT_STRIP_PIN 6                                       // Пин, к которому подключена главная лента
#define LED_COUNT 144                                           // Количество светодиодов во всей главной ленте
#define LIGHT_STRIP_BRIGHTNESS 50                               // Яркость ленты

//Настройки стоп-сигнала
// Пины
#define BRAKELIGHT_RED_PIN 9                                    // Пин для подключения красного цвета стоп-сигнала
#define BRAKELIGHT_GREEN_PIN 10                                 // Пин для подключения зеленого цвета стоп-сигнала
#define BRAKELIGHT_BLUE_PIN 11                                  // Пин для подключения синего цвета стоп-сигнала
// Свет
#define BRAKELIGHT_BRIGHTNESS 100                               // Яркость стоп-сигнала
// Анимации
#define BRAKELIGHT_ANIMATION_SPEED_ON 0                         // Скорость анимации включения стоп-сигнала. Измеряеться в миллисекундах
#define BRAKELIGHT_ANIMATION_SPEED_OFF 500                      // Скорость анимации выключения стоп-сигнала. Измеряеться в миллисекундах


#include "FastLED.h"                                            // Библиотека для адресной светодиодной ленты
#include "GyverRGB.h"                                           // Библиотека для светодиодов и обычных RGB лент

unsigned long lightStripDelayLastCalled;                        // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;                     // Переменная для замены delay() при помощи millis() в стоп-сигнале

CRGB lightStripLEDs[LED_COUNT];                                 // Обьект главной светодиодной ленты
GRGB brakeLight(BRAKELIGHT_RED_PIN, BRAKELIGHT_GREEN_PIN, BRAKELIGHT_BLUE_PIN); // Обьект стоп-сигнала
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
  lightStripCounter++;                                          // lightStripCounter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
}
