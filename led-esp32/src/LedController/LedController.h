#include <Arduino.h>

#include "Types/Color.h"
#include "Types/Effect/Effect.h"

#define PIN_R 26
#define PIN_G 25
#define PIN_B 33

class LedController{
  public:
    static void setup();
    static void setColor(Color color);
    static void setEffect(Effect effect);
  private:
};