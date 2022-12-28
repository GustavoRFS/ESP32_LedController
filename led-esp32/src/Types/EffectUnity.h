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

class EffectUnity{
  public:
    Color color;
    uint32_t duration;
    uint32_t* beforeAnimTime;
    uint32_t* afterAnimTime;
    EffectUnity(Color color, uint32_t duration){
      this->color = color;
      this->duration= duration;
      beforeAnimTime=nullptr;
      afterAnimTime=nullptr;
    }
    EffectUnity(Color color, uint32_t duration, uint32_t before, uint32_t after){
      EffectUnity(color,duration);
      this->beforeAnimTime = new uint32_t(before);
      this->afterAnimTime = new uint32_t(after);
    }
    ~EffectUnity(){
      delete beforeAnimTime;
      delete afterAnimTime;
    }
};
