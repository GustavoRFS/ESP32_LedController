#pragma once
#include <Arduino.h>

#include "Types/Color/Color.h"
#include "Types/Effect/Effect.h"
#include "definitions.h"

class LedController{
  public:
    static void setup();
    static void setColor(Color color);
    static void setEffect(Effect effect);
  private:
};