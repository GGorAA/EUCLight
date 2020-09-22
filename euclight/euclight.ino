// Настройки главной светодиодной ленты
constexpr uint8_t LIGHT_STRIP_PIN = 6;				  // Пин, к которому подключена главная лента
constexpr uint8_t LIGHT_STRIP_LED_COUNT = 144;		  // Количество светодиодов во всей главной ленте
constexpr uint8_t LIGHT_STRIP_BRIGHTNESS = 50;		  // Яркость ленты. Диапазон: 0 - 255
constexpr uint8_t LIGHT_STRIP_ANIMATION_MODIFIER = 2; // Модификатор для определения скорости ленты
constexpr uint8_t LIGHT_STRIP_ANIMATION_STEP = 2;	  // Шаг радуги. Чем больше, тем меньше
constexpr uint8_t LIGHT_STRIP_ANIMATION_MODE = 2;	  // Тип анимации. https://github.com/GGorAA/EUCLight/wiki/Animation-modes что бы узнать более

// Настройки стоп-сигнала
// Пины
constexpr uint8_t BRAKELIGHT_PIN = 5; // Пин подключения адресной ленты для стоп-сигнала
// Свет
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_ON = 255;  // Яркость включенного стоп-сигнала. Диапазон: 0 - 255
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_IDLE = 40; // Яркость бездейвствующего стоп-сигнала. Диапазон: 0 - 255
// Другое
constexpr uint8_t BRAKELIGHT_MATRIX_HEIGHT = 3;													   // Высота "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_WIDTH = 8;													   // Ширина "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_LEDCOUNT = BRAKELIGHT_MATRIX_WIDTH * BRAKELIGHT_MATRIX_HEIGHT; // Количество светодиодов в каждом отрезке. Пишеться в порядке сверху-вниз
constexpr uint8_t BRAKELIGHT_SENSITIVITY = -5;													   // Чувствительность стоп-сигнала. Чем ближе к нулю, тем чувствительнее

#define DEVICE_MODEL GotwayMcm2 // Модель моноколеса. Смотреть https://github.com/GGorAA/EUCLight для просмотра всех сущевствующих имен

// ----------------------------НАСТРОЙКИ КОНЧИЛИСЬ------------------------ //

#include "EUCSerialInterface.h"  // Библиотека для взаимодевствия с моноколесом
#include "FastLED.h"             // Библиотека для адресных светодиодных лент
#include "LightsControl.h"       // Файл для функций ленты
#include "MorsDuino.h"           // Библиотека для кода морзе

unsigned long lightStripDelayLastCalled;     // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;  // Переменная для замены delay() при помощи millis() в стоп-сигнале

unsigned long eucInfoLastUpdated = millis();

CRGB mainLightStrip[LIGHT_STRIP_LED_COUNT];
CRGB brakeLight[BRAKELIGHT_MATRIX_LEDCOUNT];

DEVICE_MODEL ElectricUnicycle(Serial, Serial);

MorsDuinoLed arduinoLED(13);

float eucSpeed;
float eucTempMileage;
float eucCurrent;
float eucTemperature;

bool isBreaking = false;
bool isReversing = false;

int eucLightStripSpeed;

void setup() {
  // Настройка пинов
  pinMode(LIGHT_STRIP_PIN, OUTPUT);
  pinMode(BRAKELIGHT_PIN, OUTPUT);

  Serial.begin(115200);
  ElectricUnicycle.setCallback(eucCallbackFunction);
  FastLED.addLeds<WS2811, LIGHT_STRIP_PIN>(mainLightStrip, LIGHT_STRIP_LED_COUNT); // Добавить главную ленту
  FastLED.addLeds<WS2811, BRAKELIGHT_PIN>(brakeLight, BRAKELIGHT_MATRIX_LEDCOUNT); // Добавить стоп-сигнал
}

void loop() {
  ElectricUnicycle.tick();
  setLightStripSpeed();
  if (eucInfoLastUpdated >= 5000) {
    stripAlert();
  }
  if (lightStripDelayLastCalled <= eucLightStripSpeed) {
    lightStripDelayLastCalled = millis();
    controlLights();
  }
}

void eucCallbackFunction(float voltage, float speed, float tempMileage, float current, float temperature, float mileage, bool dataIsNew) {
  unsigned long now = millis();

  if (dataIsNew) {
    eucInfoLastUpdated = millis();  // Сбросить счетчик

    int acceleration = calcAcceleration(speed, now);
    isBreaking = acceleration < BRAKELIGHT_SENSITIVITY;

    eucSpeed = speed;
    eucCurrent = current;
    eucTempMileage = tempMileage;
    eucTemperature = temperature;
  }
}

void setLightStripSpeed() {
  eucLightStripSpeed = LIGHT_STRIP_ANIMATION_MODIFIER * eucSpeed;
}

float calcAcceleration(float currentSpeed, unsigned long currentTime) {
  static float lastTime = 0;
  static float lastSpeed = 0;

  if (currentTime == 0) {
    return 0;
  }

  currentSpeed = abs(currentSpeed);
  float timeDelta = (float)(currentTime - lastTime) / 1000;  // secs
  float speedDelta = (currentSpeed - lastSpeed) / 3.6;       // m/s

  if (timeDelta == 0) {
    return 0;
  }
  float acceleration = speedDelta / timeDelta;  // m/s^2
  lastTime = currentTime;
  lastSpeed = currentSpeed;
  return acceleration * 3.6;  // km/h^2
}