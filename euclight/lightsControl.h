#ifndef LIGHTSCONTROL
#define LIGHTSCONTROL

#include "Settings.h"

void stripsDrawColors(int mode);

void controlLights();

void mainLightStripAnimation(int direction);

void stripAlert();

void brakeLightControl(bool state, int lightType = 1);

#endif