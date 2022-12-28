#include "Color.h"

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
    uint32_t* beforeAnimTime;
    uint32_t* afterAnimTime;
    EffectUnit(){
      color = Color();
      duration = 0;
      beforeAnimTime = new uint32_t(0);
      afterAnimTime = new uint32_t(0);
    }
    EffectUnit(Color color, uint32_t duration){
      this->color = color;
      this->duration= duration;
      beforeAnimTime=nullptr;
      afterAnimTime=nullptr;
    }
    EffectUnit(Color color, uint32_t duration, uint32_t before, uint32_t after){
      EffectUnit(color,duration);
      beforeAnimTime = new uint32_t(before);
      afterAnimTime = new uint32_t(after);
    }
    ~EffectUnit(){
      if (beforeAnimTime) delete beforeAnimTime;
      if (afterAnimTime) delete afterAnimTime;
    }
};
