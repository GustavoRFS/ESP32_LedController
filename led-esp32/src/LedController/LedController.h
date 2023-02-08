#pragma once
#include <Arduino.h>

#include "Types/Color/Color.h"
#include "Types/Effect/Effect.h"
#include "Types/Gradient.h"
#include "definitions.h"

class LedController
{
public:
  static void setup();
  static void setColor(Color color);
  static void setEffect(Effect *effect);
  static void setGradient(Gradient *gradient);
  static void turnOn();
  static void turnOff();
  static void increaseBrightness();
  static void decreaseBrightness();

private:
};