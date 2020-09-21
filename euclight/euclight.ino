#include "EUCSerialInterface.h"  // Библиотека для взаимодевствия с моноколесом
#include "FastLED.h"             // Библиотека для адресных светодиодных лент
#include "MorsDuino.h"           // Библиотека для кода морзе
#include "Settings.h"            // Файл с настройками
#include "LightsControl.h"       // Файл для функций ленты

unsigned long lightStripDelayLastCalled;     // Переменная для замены delay() при помощи millis() в главной ленте
unsigned long brakeLightOffDelayLastCalled;  // Переменная для замены delay() при помощи millis() в стоп-сигнале

unsigned long eucInfoLastUpdated = millis();

CRGB mainLightStrip[LIGHT_STRIP_LED_COUNT];
CRGB brakeLight[BRAKELIGHT_MATRIX_LEDCOUNT];

DEVICE_MODEL ElectricUnicycle(Serial, Serial);

MorsDuino arduinoLED(13, 1);

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
    FastLED.addLeds<WS2811, LIGHT_STRIP_PIN>(mainLightStrip, LIGHT_STRIP_LED_COUNT);
    FastLED.addLeds<WS2811, BRAKELIGHT_PIN>(brakeLight, BRAKELIGHT_MATRIX_LEDCOUNT);
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