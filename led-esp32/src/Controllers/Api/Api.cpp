#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include "Logger/Logger.h"
#include "WiFiManager/WifiManager.h"
#include "Api.h"
#include "Controllers/ControllerWS/ControllerWS.h"
#include "UpdateService/UpdateService.h"

#include "definitions.h"

#ifdef DEVELOPMENT
  #include "Utils/Utils.h"
#endif

void Api::sendResponse(int code,String responseBody,AsyncWebServerRequest *request){
  AsyncWebServerResponse* response=request->beginResponse(code,"text/html",responseBody);

  #ifdef DEVELOPMENT
  response->addHeader("Access-Control-Allow-Origin","*");
  #endif
  
  request->send(response);
} 

void Api::registerRoutes(AsyncWebServer &server){
  server.on("/api/is-connected-to-wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    String response;

    if (WiFi.isConnected()){
      response="true";
    }
    else{
      response="false";
    }
    
    sendResponse(200,response,request);
  });

  server.on("/api/connect-to-wifi",HTTP_POST,[](AsyncWebServerRequest* request){},NULL,
  [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
    StaticJsonDocument<32> doc;

    DeserializationError error = deserializeJson(doc, data, len);

    if (error) return Logger::error("deserializeJson() failed: " + String(error.c_str()));

    const char* SSID = doc["SSID"]; 
    const char* PWD = doc["PWD"];

    WifiManager::connect(String(SSID),String(PWD));

    sendResponse(200,"OK",request);
  });

  server.on("/api/update", HTTP_POST, [](AsyncWebServerRequest *request){
    if (!UpdateService::checkForUpdate()) return sendResponse(400,"Não há atualizações",request);

    sendResponse(200,"OK",request);

    UpdateService::update();
  });

  server.on("/api/has-updates", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!UpdateService::checkForUpdate()) return sendResponse(404,"Não há atualizações",request);
    
    sendResponse(200,"OK",request);
  });

  #ifdef DEVELOPMENT
  server.on("/api/dirs", HTTP_GET, [](AsyncWebServerRequest *request){
    sendResponse(200,Utils::listDirectories("/",4),request);
  });
  #endif

  server.on("/api/download-assets", HTTP_POST, [](AsyncWebServerRequest *request){
    sendResponse(200,"OK",request);

    UpdateService::downloadAssets();
  });
  server.on("/api/*", HTTP_ANY, [](AsyncWebServerRequest *request){
    sendResponse(404,"Cannot "+String(request->methodToString())+" "+request->url(),request);
  });
}

