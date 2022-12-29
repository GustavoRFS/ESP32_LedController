#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Color{
  public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color(){}
    Color(uint8_t r,uint8_t g,uint8_t b);
    static Color parseFromJSON(JsonObject &doc);
};