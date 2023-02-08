#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Color{
  public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color(){}
    Color(const Color& color);
    Color(uint8_t r,uint8_t g,uint8_t b);
    Color(JsonObject &doc);
};