
void mainLightStripAnimation(int direction)
{
  byte lightStripCounter;

  for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++)
  { // От 0 до первой трети
    // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
  lightStripCounter++; // lightStripCounter меняется от 0 до 255 (тип данных byte)
}

void rainbowMode(int direction)
{
  static byte hue = 0;
  hue++;
  for (byte i = 0; i < M_WIDTH; i++)
  {
    LEDdata thisColor = mHSV((byte)(hue + i * float(255 / M_WIDTH)), 255, 255);
    for (byte j = 0; j < M_HEIGHT; j++)
      matrix.setPix(i, j, thisColor);
  }
}

void alertMode()
{
  for (int i = 0; i <= LIGHT_STRIP_LED_COUNT; i++)
  {
    mainLightStrip.setHEX(i, 0xFF6565);
  }
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

void brakeLightControl(bool state, int lightType = 1)
{
  if (state == true)
  {
    if (lightType == 1)
    {
      brakeLight.fadeTo(255, 0, 0, 0);
    }
    else if (lightType == 2)
    {
      brakeLight.fadeTo(255, 255, 255, 0);
    }
    else if (lightType == 3)
    {
    }
  }
  else if (state == false)
  {
    brakeLight.setBrightness(BRAKELIGHT_BRIGHTNESS_IDLE);
  }
}