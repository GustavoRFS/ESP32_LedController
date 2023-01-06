#pragma once
#include <Arduino.h>

class Logger{
  public:
    static void log(String content);
    static void error(String content);
    static void config();
    static tm timeinfo;
};