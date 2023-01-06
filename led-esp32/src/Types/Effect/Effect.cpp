#include "Effect.h"

Effect::Effect(uint8_t size){
  this->size=size;
  keyColors=new EffectUnit[size];
}

Effect::Effect(EffectUnit* effectUnit, uint8_t size):Effect(size){
  for (int i=0; i<size;i++){
    keyColors[i] = effectUnit[i];
  }
}

Effect::Effect(JsonObject &doc){
  bool custom = doc["custom"];

  if (custom) {
    JsonArray jsonKeyColors= doc["keyColors"].as<JsonArray>();

    keyColors = new EffectUnit[jsonKeyColors.size()];

    for (uint16_t i=0;i<jsonKeyColors.size();i++){
      JsonObject keyColor = jsonKeyColors[i];

      JsonObject color = keyColor["color"];
      uint8_t r = color["r"]; // 100, 100, 100, 100, 100, 100, 100, 100, 100, ...
      uint8_t g = color["g"]; // 100, 100, 100, 100, 100, 100, 100, 100, 100, ...
      uint8_t b = color["b"]; // 100, 100, 100, 100, 100, 100, 100, 100, 100, ...

      uint32_t duration = keyColor["duration"]; // 100, 100, 100, 100, 100, 100, 100, 100, 100, ...
      uint32_t beforeSoftAnimTime = keyColor["beforeSoftAnimTime"]; // 100, 100, 100, 100, 100, ...
      uint32_t afterSoftAnimTime = keyColor["afterSoftAnimTime"]; // 100, 100, 100, 100, 100, ...

      addKeyColor(EffectUnit(Color(r,g,b),duration,beforeSoftAnimTime,afterSoftAnimTime),i);
    }
    return;
  }

  String effect = doc["effect"];
  
  #ifdef DEVELOPMENT
  Serial.println(effect);
  #endif
}

void Effect::addKeyColor(EffectUnit keyColor,uint8_t position){
  this->keyColors[position] = keyColor;
}

Effect::~Effect(){
  if (keyColors) delete keyColors;
}