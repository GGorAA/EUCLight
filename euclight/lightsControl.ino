
void controlLights()
{
  if (millis() - lightStripDelayLastCalled >= eucLightStripSpeed)
  {                                       // Задержка
    lightStripDelayLastCalled = millis(); // Заново считать время

    switch (isBreaking)
    { // Если моноколесо ускоряеться
    case 1:
      brakeLightControl(false);   // Выключить стоп-сигнал
      mainLightStripAnimation(1); // Анимация главной светодиодной ленты
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
    switch (isBreaking)
    {
    case true:
      if (isReversing)
      {
        brakeLightControl(true, 2);
        mainLightStripAnimation(2);
      }
      else
      {
        brakeLightControl(true, 1);
        mainLightStripAnimation(1);
      }
      break;
    case false:
      if (isReversing)
      {
        brakeLightControl(false);
        mainLightStripAnimation(2);
      }
      else
      {
        brakeLightControl(false);
        mainLightStripAnimation(1);
      }
    default:
      break;
    }
  }
}

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
  for (byte i = 0; i < BRAKELIGHT_MATRIX_WIDTH; i++)
  {
    LEDdata thisColor = mHSV((byte)(hue + i * float(255 / BRAKELIGHT_MATRIX_WIDTH)), 255, 255);
    for (byte j = 0; j < BRAKELIGHT_MATRIX_HEIGHT; j++)
      mainLightStrip.setPix(i, j, thisColor);
  }
}

void alertMode()
{
  for (int i = 0; i < 3; i++)
  {
    for (int i2 = 0; i2 <= LIGHT_STRIP_LED_COUNT; i2++)
    {
      mainLightStrip.setHEX(i2, 0xFF6565);
    }
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
  }
}