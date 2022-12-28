#include <Arduino.h>
#include "LedController.h"

void LedController::setup(){
  pinMode(PIN_R,OUTPUT);
  pinMode(PIN_G,OUTPUT);
  pinMode(PIN_B,OUTPUT);
}

void LedController::setColor(uint8_t r,uint8_t g,uint8_t b){
  analogWrite(PIN_R,r);
  analogWrite(PIN_G,g);
  analogWrite(PIN_B,b);
}