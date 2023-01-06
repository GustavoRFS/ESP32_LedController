#pragma once
#include <Arduino.h>
#include "Types/Color/Color.h"

#define CONFIG_FILENAME "/cfg"

class SettingsManager {
  private:
    void getSettingsFromFile();
    void saveSettingsToFile();
    void setDefaults();
  public:
    void setWifi(String SSID,String PWD);
    void setLastColor(Color color);
    String* wifiSSID;
    String* wifiPassword;
    Color* lastColor;
    void setup();
    static SettingsManager& getInstance();
};