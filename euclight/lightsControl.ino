
void mainLightStripAnimation() {
  byte lightStripCounter;

  for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++ ) {                        // От 0 до первой трети
          // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  lightStripCounter++;                                          // lightStripCounter меняется от 0 до 255 (тип данных byte)
}

/*void brakeLightControl(bool state, int lightType = 1) {       // Функция для контроля заднего света
  if (state == true) {                                          // Если надо включить
    if (lightType == 1) {                                       // Если тип света торможение
      brakeLight.fadeTo(RED, BRAKELIGHT_ANIMATION_SPEED_ON);    // Установить красный свет
    } else if (lightType == 2) {                                // Если тип света для движения назад
      brakeLight.fadeTo(WHITE, BRAKELIGHT_ANIMATION_SPEED_ON);  // Установить белый цвет
    }
  } else if (state == false) {                                  // Если надо выключить
      brakeLight.fadeTo(BLACK, BRAKELIGHT_ANIMATION_SPEED_OFF); // Выключить свет
  }
}*/

void brakeLightControl(bool state, int lightType = 1) {
  if (state == true) {
    if (lightType == 1) {
      brakeLight.fadeTo(255, 0, 0, BRAKELIGHT_ANIMATION_SPEED_ON);
    } else if (lightType == 2) {
      brakeLight.fadeTo(255, 255, 255, BRAKELIGHT_ANIMATION_SPEED_ON);
    } 
  } else if (state == false) {
    //brakeLight.setBrightness();
  }
}