#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "WiFiManager/WifiManager.h"
#include "SPARoutes/SPARoutes.h"
#include "ControllerWS/ControllerWS.h"
#include "APIRoutes/APIRoutes.h"
#include "Logger/Logger.h"
#include "SettingsManager/SettingsManager.h"
#include "LedController/LedController.h"

// #define USE_LITTLEFS
#include <FS.h>
#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif 


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    #ifdef ARDUINO_ARCH_ESP8266
    File root = fs.open(dirname, "r");
    #else
    File root = fs.open(dirname);
    #endif

    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                #ifdef ARDUINO_ARCH_ESP8266
                listDir(fs, file.fullName(), levels -1);
                #else
                listDir(fs, file.path(), levels -1);
                #endif
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);
  Logger::config();

  if (!SPIFFS.begin()) {
		Logger::error("SPIFFS MOUNT FAIL");
	}
  
  listDir(SPIFFS,"/",6);

  LedController::setup();
  SettingsManager::getInstance().setup();
  Color color = *SettingsManager::getInstance().lastColor;
  LedController::setColor(color.r,color.g,color.b); 

  WifiManager::setup();
  ControllerWS::registerWebSocket(server);
  APIRoutes::registerRoutes(server);
  SPARoutes::registerRoutes(server);

  server.begin();
}
 
void loop() {
  
}

