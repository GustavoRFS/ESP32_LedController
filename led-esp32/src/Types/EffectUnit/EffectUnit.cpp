#include "EffectUnit.h"

EffectUnit::EffectUnit(Color color, uint32_t duration, uint32_t before, uint32_t after){
  this->color = color;
  this->duration = duration;
  beforeAnimTime = before;
  afterAnimTime = after;
}