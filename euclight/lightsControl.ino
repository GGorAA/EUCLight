void stripsDrawColors(int mode) // Рисует на светодиодах базовые рисунки, с которыми будет потом взаимодействовать анимация
{
  if (mode == 1)
  {
    for (int i = 0; i < LIGHT_STRIP_LED_COUNT; i++)                                                    // Отрисовка радуги на главной ленте
    {                                                                                                  // от 0 до первой трети
      mainLightStrip.setHSV(i * LIGHT_STRIP_ANIMATION_STEP, mainLightStripAnimationCounter, 100, 100); // HSV. Увеличивать HUE (цвет)
    }
  }
}

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
    rainbowMode(direction);
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

void rainbowMode(int direction)
{
  if (direction == 1)
  {
    for (int i = 0; i <= LIGHT_STRIP_LED_COUNT; i++)
    {

      switch (i)
      {
      case 0:
        mainLightStrip[i] = mainLightStrip[LIGHT_STRIP_LED_COUNT];
        break;
      case LIGHT_STRIP_LED_COUNT:
        mainLightStrip[i] = 
      default:
        break;
      }
      
      mainLightStrip[i] = mainLightStrip
    }
    
  }
  
}

void alertMode()
{
  fill_solid(&(leds[i]), LIGHT_STRIP_LED_COUNT, CRGB(255, 40, 40));
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