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

//TODO: handle empty array github

AsyncWebServer server(80);

void setup() {
  #ifdef DEVELOPMENT
  Serial.begin(460800);
  #endif

  Logger::config();

  if (!SPIFFS.begin()) {
		Logger::error("SPIFFS MOUNT FAIL");
	}

  LedController::setup();
  SettingsManager::getInstance().setup();
  Color color = *SettingsManager::getInstance().lastColor;
  LedController::setColor(color); 
  WifiManager::setup();
  UpdateService::setup();
  ControllerWS::registerWebSocket(server);
  APIRoutes::registerRoutes(server);
  SPARoutes::registerRoutes(server);

  server.begin();
}
 
void loop() {
  vTaskDelete(NULL);
}

