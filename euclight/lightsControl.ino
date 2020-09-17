
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

void mainLightStripAnimation(int direction, int mode)
{
  if (mode == 1)
  {
    rainbowMode(direction);
  }
  else if (mode == 2)
  {
    blueWhiteMode(direction);
  }
}

void rainbowMode(int direction)
{
  byte counter;
  if (direction == 1)
  {
    for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++)
    {                                                                                 // от 0 до первой трети
      mainLightStrip.setHSV(counter + i * LIGHT_STRIP_ANIMATION_STEP, 255, 100, 100); // HSV. Увеличивать HUE (цвет)
    }
    counter++; // counter меняется от 0 до 255 (тип данных byte)
    mainLightStrip.show();
  }
  else if (direction == 2)
  {
    for (int i = LIGHT_STRIP_LED_COUNT; i <= 0; i--)
    {                                                                                 // от 0 до первой трети
      mainLightStrip.setHSV(counter + i * LIGHT_STRIP_ANIMATION_STEP, 255, 100, 100); // HSV. Увеличивать HUE (цвет)
    }
    counter++; // counter меняется от 0 до 255 (тип данных byte)
    mainLightStrip.show();
  }
}

void blueWhiteMode(int direction) {

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