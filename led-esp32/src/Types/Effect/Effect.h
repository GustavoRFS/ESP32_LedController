#include <ArduinoJson.h>

#include "Types/EffectUnit.h"

class Effect{
  public:
    EffectUnit* keyColors;
    uint8_t size;
    Effect(){}
    Effect(uint8_t size);
    Effect(EffectUnit* effectUnit,uint8_t size);
    Effect(JsonObject &doc);
    void addKeyColor(EffectUnit effectUnit, uint8_t position);
    ~Effect();
  private:
    static Effect parseCustomEffectFromJSON(JsonObject &doc);
};