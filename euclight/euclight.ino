// Настройки главной светодиодной ленты
#define LIGHT_STRIP_PIN = 6;                 // Пин, к которому подключена главная лента
#define LIGHT_STRIP_LED_COUNT 144;         // Количество светодиодов во всей главной ленте
#define LIGHT_STRIP_BRIGHTNESS 50;         // Яркость ленты. Диапазон: 0 - 255
#define LIGHT_STRIP_ANIMATION_MODIFIER 2;  // Модификатор для определения скорости ленты
#define LIGHT_STRIP_ANIMATION_STEP 2;      // Шаг радуги. Чем больше, тем меньше
#define LIGHT_STRIP_ANIMATION_MODE 2;      // Тип анимации. https://github.com/GGorAA/EUCLight/wiki/Animation-modes что бы узнать более

// Настройки стоп-сигнала
// Пины
#define BRAKELIGHT_PIN 5;  // Пин подключения адресной ленты для стоп-сигнала
// Свет
#define BRAKELIGHT_BRIGHTNESS_ON 255;   // Яркость включенного стоп-сигнала. Диапазон: 0 - 255
#define BRAKELIGHT_BRIGHTNESS_IDLE 40;  // Яркость бездейвствующего стоп-сигнала. Диапазон: 0 - 255
// Другое
#define BRAKELIGHT_MATRIX_HEIGHT 3;                                                     // Высота "матрицы" стоп-сигнала
#define BRAKELIGHT_MATRIX_WIDTH 8;                                                      // Ширина "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_LEDCOUNT = BRAKELIGHT_MATRIX_WIDTH * BRAKELIGHT_MATRIX_HEIGHT;  // Количество светодиодов в каждом отрезке. Пишеться в порядке сверху-вниз
#define BRAKELIGHT_SENSITIVITY -5;                                                      // Чувствительность стоп-сигнала. Чем ближе к нулю, тем чувствительнее

#define DEVICE_MODEL GotwayMcm2  // Модель моноколеса. Смотреть https://github.com/GGorAA/EUCLight для просмотра всех сущевствующих имен

// ----------------------------НАСТРОЙКИ КОНЧИЛИСЬ------------------------ //

#include "EUCSerialInterface.h"  // Библиотека для взаимодевствия с моноколесом
#include "FastLED.h"             // Библиотека для адресных светодиодных лент
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
  ElectricUnicycle.setCallback(eucCallbackFunction);                                // Функция которая будет запущена библиотекой EUCSerialInterface при каждом вызове ElectricUnicycle.tick()
  FastLED.addLeds<WS2811, LIGHT_STRIP_PIN>(mainLightStrip, LIGHT_STRIP_LED_COUNT);  // Добавить главную ленту
  FastLED.addLeds<WS2811, BRAKELIGHT_PIN>(brakeLight, BRAKELIGHT_MATRIX_LEDCOUNT);  // Добавить стоп-сигнал
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

    int acceleration = calcAcceleration(speed, eucInfoLastUpdated);
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

// Я хз как этот код работает. Я его просто скопипастил. Не обращайте внимания, он просто работает
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

// -------------------------------------КОНТРОЛЬ СВЕТОДИОДНЫМИ ЛЕНТАМИ------------------------------------- //

void stripsDrawColors(int mode)  // Рисует на светодиодах базовые рисунки, с которыми будет потом взаимодействовать анимация
{
  if (mode == 1) {
    fill_rainbow(&(mainLightStrip[0]), LIGHT_STRIP_LED_COUNT, 222 /*starting hue*/);  // Нарисовать радугу
  }
}

void controlLights() {
  if (millis() - lightStripDelayLastCalled >= eucLightStripSpeed) {  // Задержка
    lightStripDelayLastCalled = millis();                            // Заново считать время

    switch (isBreaking) {
      case true:
        if (isReversing) {
          brakeLightControl(true, 2);
          mainLightStripAnimation(2);
        } else {
          brakeLightControl(true, 1);
          mainLightStripAnimation(1);
        }
        break;
      case false:
        if (isReversing) {
          brakeLightControl(false);    // Выключить стоп-сигнал
          mainLightStripAnimation(2);  // Анимация главной светодиодной ленты
        } else {
          brakeLightControl(false);
          mainLightStripAnimation(1);
        }
      default:
        break;
    }
  }
}

void mainLightStripAnimation(int direction) {
  if (direction == 1) {
    for (int i = 0; i > LIGHT_STRIP_LED_COUNT; i++) {
      switch (i) {
        case 0:
          mainLightStrip[i] = mainLightStrip[LIGHT_STRIP_LED_COUNT];
          break;

        default:
          mainLightStrip[i] = mainLightStrip[i - 1];
          break;
      }
    }
  } else if (direction == 2) {
    for (int i = 0; i > LIGHT_STRIP_LED_COUNT; i++) {
      switch (i) {
        case LIGHT_STRIP_LED_COUNT:
          mainLightStrip[i] = mainLightStrip[0];
          break;

        default:
          mainLightStrip[i] = mainLightStrip[i + 1];
          break;
      }
    }
  }
}

/*void rainbowMode(int direction)
{
  if (direction == 1)
  {
    for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++)
    {                                                                                                  // от 0 до первой трети
      mainLightStrip.setHSV(i * LIGHT_STRIP_ANIMATION_STEP, mainLightStripAnimationCounter, 100, 100); // HSV. Увеличивать HUE (цвет)
    }
    mainLightStripAnimationCounter++; // mainLightStripAnimationCounter меняется от 0 до 255 (тип данных byte)
    mainLightStrip.show();
  }
  else if (direction == 2)
  {
    for (int i = LIGHT_STRIP_LED_COUNT; i <= 0; i--)
    {                                                                                                  // от 0 до первой трети
      mainLightStrip.setHSV(i * LIGHT_STRIP_ANIMATION_STEP, mainLightStripAnimationCounter, 100, 100); // HSV. Увеличивать HUE (цвет)
      mainLightStripAnimationCounter++;                                                                // counter меняется от 0 до 255
    }
    mainLightStrip.show();
  }
}*/

void stripAlert() {
  fill_solid(&(mainLightStrip[0]), LIGHT_STRIP_LED_COUNT, CRGB(255, 40, 40));
}

void brakeLightControl(bool state, int lightType = 1) {
  /*if (state == true)
  {
    if (lightType == 1)
    {
      for (int i = 0; i < BRAKELIGHT_MATRIX_HEIGHT; i++)
      {
        for (int i2 = 0; i2 < BRAKELIGHT_MATRIX_WIDTH; i2++)
        {
          brakeLight.setPix(i, i2, mHEX(0xFF3A3A));
        }
      }
    }
    else if (lightType == 2)
    {
      for (int i = 0; i < BRAKELIGHT_MATRIX_HEIGHT; i++)
      {
        for (int i2 = 0; i2 < BRAKELIGHT_MATRIX_WIDTH; i2++)
        {
          brakeLight.setPix(i, i2, mHEX(0xFFFFFF));
        }
      }
    }
    else if (lightType == 3)
    {
    }
  }
  else if (state == false)
  {
    brakeLight.setBrightness(BRAKELIGHT_BRIGHTNESS_IDLE);
  }*/
}