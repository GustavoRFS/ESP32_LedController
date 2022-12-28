#include <ArduinoJson.h>

#include "Types/EffectUnity.h"

class Effect{
  public:
    bool custom;
    EffectUnity[] keyColors;
    Effect();
    Effect(JsonObjectConst &doc);
  private:
    static Effect parseCustomEffectFromJSON(JsonObjectConst &doc);
};