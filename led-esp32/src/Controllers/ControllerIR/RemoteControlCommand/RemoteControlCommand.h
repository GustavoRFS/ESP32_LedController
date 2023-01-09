#include <Arduino.h>

#include "Types/Color/Color.h"
#include "Types/Effect/Effect.h"

class RemoteControlCommand{
  public:
    uint8_t remoteControlCodesAmount;
    uint32_t* remoteControlCodes;
    Color* color;
    Effect* effect;
    uint8_t* switchPower;
    uint8_t* changeBrightness;
    void performCommand();

    RemoteControlCommand(Color color,uint32_t* remoteControlCodes,uint8_t remoteControlCodesAmount);
    RemoteControlCommand(Effect* effect,uint32_t* remoteControlCodes,uint8_t remoteControlCodesAmount);
    RemoteControlCommand(bool powerOn,uint32_t* remoteControlCodes,uint8_t remoteControlCodesAmount);
    RemoteControlCommand(uint32_t* remoteControlCodes,uint8_t remoteControlCodesAmount,bool changeBrightness);
    ~RemoteControlCommand();
};