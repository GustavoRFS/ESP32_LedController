#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "WiFiManager/WifiManager.h"
#include "SPARoutes/SPARoutes.h"
#include "Controllers/ControllerWS/ControllerWS.h"
#include "Controllers/Api/Api.h"
#include "Logger/Logger.h"
#include "SettingsManager/SettingsManager.h"
#include "LedController/LedController.h"
#include "UpdateService/UpdateService.h"
#include "Utils/Utils.h"
#include <FS.h>

#include "definitions.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif

AsyncWebServer server(80);

void setup() {
  #ifdef DEVELOPMENT
  Serial.begin(460800);
  #endif

  Logger::config();
  SettingsManager* settings = SettingsManager::getInstance();

  if (!SPIFFS.begin()) {
    Logger::error("SPIFFS MOUNT FAIL");
    settings->FSError = true;
  }
  else settings->FSError = false;


  LedController::setup();
  settings->setup();
  Color color = *settings->lastColor;
  LedController::setColor(color); 
  ControllerWS::registerWebSocket(server);
  APIRoutes::registerRoutes(server);
  SPARoutes::registerRoutes(server);
  WifiManager::setup();
  UpdateService::setup();

  server.begin();

  if (settings->FSError){
    // Recovery mode
  }
}
 
void loop() {
  vTaskDelete(NULL);
}

