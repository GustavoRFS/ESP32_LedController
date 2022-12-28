#include <Arduino.h>
#include "LedController.h"

void LedController::setup(){
  pinMode(PIN_R,OUTPUT);
  pinMode(PIN_G,OUTPUT);
  pinMode(PIN_B,OUTPUT);
}

void LedController::setColor(Color color){
  analogWrite(PIN_R,color.r);
  analogWrite(PIN_G,color.g);
  analogWrite(PIN_B,color.b);
}

void LedController::setEffect(Effect effect){
}