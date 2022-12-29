#include "Color.h"

Color::Color(uint8_t r,uint8_t g,uint8_t b){
  this->r=r;
  this->g=g;
  this->b=b;
}

Color Color::parseFromJSON(JsonObject& doc){
  uint8_t r = doc["r"];
  uint8_t g = doc["g"];
  uint8_t b = doc["b"];

  return Color(r,g,b);
}