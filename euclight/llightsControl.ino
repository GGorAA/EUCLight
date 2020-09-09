
void brakeLightControl(bool state, int lightType = 0) {         // Функция для контроля заднего света
  if (state == true) {                                          // Если надо включить
    if (lightType == 0) {                                       // Если тип света обычный, красный
      brakeLight.fadeTo(RED, BRAKELIGHT_ANIMATION_SPEED_ON)
    } else if (lightType == 1) {
      brakeLight.fadeTo(WHITE, BRAKELIGHT_ANIMATION_SPEED_ON)
    }
  } else if (state == false) {
    if (lightType == 0) {
      brakeLight.fadeTo(BLACK, BRAKELIGHT_ANIMATION_SPEED_OFF)
    } else if (lightType == 1) {
      for (int i = 100; 1 <= 100; i--) {
        int brightness = map(i, 0, 100, 0, 255); 
        brakeLight.setBrightness(brightness)
        delay(10)
      } 
    }
  }
}