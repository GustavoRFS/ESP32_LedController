#include <Arduino.h>

#include "Logger.h"
#include "definitions.h"

void Logger::config(){
  const int GMT_BR = -3 * 3600;
  configTime(GMT_BR, 3600, "pool.ntp.org");
}

void Logger::log(String content){
  // tm time; 
  // getLocalTime(&time);
  // Serial.print(&time, "[%A, %B %d %Y %H:%M:%S] - ");
  #ifdef DEVELOPMENT
  Serial.println("INFO: "+content);
  #else
  #endif
}

void Logger::error(String content){
  // struct tm time; 
  // getLocalTime(&time);
  // Serial.print(&time, "[%A, %B %d %Y %H:%M:%S] - ");

  #ifdef DEVELOPMENT
  Serial.println("ERROR: "+content);
  #else
  #endif
}