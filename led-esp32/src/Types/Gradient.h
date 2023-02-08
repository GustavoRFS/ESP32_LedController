#pragma once
#include <ArduinoJson.h>

#include "Types/Color/Color.h"

class GradientUnit
{
public:
  Color color;
  uint8_t percentage;
  GradientUnit(Color color, uint8_t percentage)
  {
    this->color = color;
    this->percentage = percentage;
  }
  GradientUnit() {}
};

class Gradient
{
public:
  GradientUnit *units;
  uint8_t size;
  Gradient(JsonArray &jsonArray)
  {
    size = jsonArray.size();
    units = new GradientUnit[size];
    for (uint8_t i = 0; i < size; i++)
    {
      units[i] = GradientUnit(Color(jsonArray[i]["color"]["r"], jsonArray[i]["color"]["g"], jsonArray[i]["color"]["b"]), jsonArray[i]["percentage"]);
    }
  }
  ~Gradient()
  {
    if (units)
      delete[] units;
  }
};
