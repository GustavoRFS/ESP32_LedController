#pragma once
#include "Types/Color/Color.h"
/*
  [
    {
      color:{
        r:100,
        g:100,
        b:100,
      },
      duration: 100, //100 time units
      beforeSoftAnimTime:100, // 100 time units
      afterSoftAnimTime:100 // 100 time units
    }
  ]
*/

class EffectUnit{
  public:
    Color color;
    uint32_t duration;
    uint32_t beforeAnimTime;
    uint32_t afterAnimTime;
    EffectUnit(){};
    EffectUnit(Color color, uint32_t duration, uint32_t before, uint32_t after);
};
