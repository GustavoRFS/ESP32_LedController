#include "Color.h"

Color::Color(const Color& color){
  this->r=color.r;
  this->g=color.g;
  this->b=color.b;
}

Color::Color(uint8_t r,uint8_t g,uint8_t b){
  this->r=r;
  this->g=g;
  this->b=b;
}

Color::Color(JsonObject &doc){
  this->r = doc["r"].as<uint8_t>();
  this->g = doc["g"].as<uint8_t>();
  this->b = doc["b"].as<uint8_t>();

}