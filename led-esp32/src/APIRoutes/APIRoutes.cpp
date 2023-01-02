#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include "Logger/Logger.h"
#include "WiFiManager/WifiManager.h"
#include "APIRoutes.h"
#include "ControllerWS/ControllerWS.h"
#include "UpdateService/UpdateService.h"

void APIRoutes::registerRoutes(AsyncWebServer &server){
  server.on("/api/is-connected-to-wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    String response;

    if (WiFi.isConnected()){
      response="true";
    }
    else{
      response="false";
    }
    
    request->send(200,"text/html",response);
  });

  server.on("/api/connect-to-wifi",HTTP_POST,[](AsyncWebServerRequest* request){},NULL,
  [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
    StaticJsonDocument<32> doc;

    DeserializationError error = deserializeJson(doc, data, len);

    if (error) return Logger::error("deserializeJson() failed: " + String(error.c_str()));

    const char* SSID = doc["SSID"]; 
    const char* PWD = doc["PWD"];

    WifiManager::connect(String(SSID),String(PWD));

    return request->send(200,"text/html","OK");
  });

  server.on("/api/update", HTTP_POST, [](AsyncWebServerRequest *request){
    if (!UpdateService::checkForUpdate()) return request->send(400,"text/html","Não há atualizações");

    request->send(200,"text/html","OK");

    UpdateService::update();
  });
}

