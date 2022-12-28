#include <Arduino.h>

#define PIN_R 26
#define PIN_G 25
#define PIN_B 33

class LedController{
  public:
    static void setup();
    static void setColor(uint8_t r,uint8_t g,uint8_t b);
  private:
};