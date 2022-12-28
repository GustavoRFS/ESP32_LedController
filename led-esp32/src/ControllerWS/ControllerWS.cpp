#include <ArduinoJson.h>

#include "ControllerWS.h"
#include "LedController/LedController.h"
#include "Logger/Logger.h"
#include "Types/Color.h"
#include "Types/Effect/Effect.h"

AsyncWebSocket *ws = new AsyncWebSocket("/api/ws");

AsyncWebSocket* ControllerWS::WebSocket(){
  return ws;
}

void parseJSONMessage(uint8_t *data, size_t len){
  DynamicJsonDocument doc(3072); //Worst case with custom effect with 20 elements

  DeserializationError error = deserializeJson(doc, data, len);

  if (error) return Logger::error("deserializeJson() failed: " + String(error.c_str()));

  const char* event = doc["event"];

  JsonObject jsonData = doc["data"];

  if (event == "color") return LedController::setColor(Color::parseFromJSON(jsonData));
  
  LedController::setEffect(Effect(jsonData));
}

void ControllerWS::handleWebSocketMessage( uint8_t *data, size_t len) {
  // AwsFrameInfo *info = (AwsFrameInfo*)arg;
  // if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    
  // }

  for (size_t i=0;i<len;i++){
    Serial.write(data[i]);
  }
  
  //Deserialize JSON
  /*
  {
    event:"color"||"effect",
    data:{

    }
  }
  */
  
}

void ControllerWS::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                            void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage( data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void ControllerWS::setup(){
  ws->onEvent(onEvent);
}

void ControllerWS::registerWebSocket(AsyncWebServer& server){
  setup();
  server.addHandler(ws);
}