#pragma once
#include <ESPAsyncWebServer.h>

class Api{
  public:
    static void registerRoutes(AsyncWebServer &server);
  private:
    static void sendResponse(int code,String responseBody,AsyncWebServerRequest *request);
};