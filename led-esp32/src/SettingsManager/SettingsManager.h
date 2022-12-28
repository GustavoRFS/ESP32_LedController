#include <Arduino.h>
#include "Types/Color.h"

#define CONFIG_FILENAME "/cfg"

class SettingsManager {
  private:
    void getSettingsFromFile();
    void saveSettingsToFile();
    void testJsonRead();
    void setDefaults();
  public:
    String* wifiSSID;
    String* wifiPassword;
    Color* lastColor;
    String* lastEffect;
    void setup();
    static SettingsManager& getInstance();
};