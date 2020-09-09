
void lightStripAnimation() {
  byte lightStripCounter;

  for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++ ) {                        // От 0 до первой трети
          // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  lightStripCounter++;                                          // lightStripCounter меняется от 0 до 255 (тип данных byte)
}

void brakeLightControl(bool state, int lightType = 0) {         // Функция для контроля заднего света
  if (state == true) {                                          // Если надо включить
    if (lightType == 0) {                                       // Если тип света торможение
      brakeLight.fadeTo(RED, BRAKELIGHT_ANIMATION_SPEED_ON)     // Установить красный свет
    } else if (lightType == 1) {                                // Если тип света для движения назад
      brakeLight.fadeTo(WHITE, BRAKELIGHT_ANIMATION_SPEED_ON)   // Установить белый цвет
    }
  } else if (state == false) {                                  // Если надо выключить
      brakeLight.fadeTo(BLACK, BRAKELIGHT_ANIMATION_SPEED_OFF)  // Выключить свет
  }
}