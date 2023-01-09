#include <IRremote.h>

#include "IRMatrix/IRMatrix.h"
#include "ControllerIR.h"
#include "definitions.h"

IRrecv receiver(IR_PIN);

void ControllerIR::setup(){
  receiver.start();
}

bool ControllerIR::available(){
  return receiver.available();
}

void ControllerIR::read(){
  IRData *data = receiver.read();
  Serial.println(data->address);
  Serial.println(data->command);
  Serial.println(data->decodedRawData);
}

void ControllerIR::readAndPerformCommand(){
  read();
  uint32_t code=1;

  for (uint8_t i=0;i<16;i++){
    for (uint8_t j=0;j<IRMatrix[i].remoteControlCodesAmount;j++){
      if (code == IRMatrix[i].remoteControlCodes[j]){
        return IRMatrix[i].performCommand();
      }
    }
  }
}

 