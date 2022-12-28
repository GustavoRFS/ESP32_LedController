#include <Arduino.h>
#include <ArduinoJson.h>

class Color{
  public:
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    Color(){}
    Color(u_int8_t r,u_int8_t g,u_int8_t b){
      this->r=r;
      this->g=g;
      this->b=b;
    }
    static Color parseFromJSON(JsonObject &doc);
};