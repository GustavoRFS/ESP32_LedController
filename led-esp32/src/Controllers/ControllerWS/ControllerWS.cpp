#include <ArduinoJson.h>

#include "UpdateService/UpdateService.h"
#include "ControllerWS.h"
#include "LedManager/LedManager.h"
#include "Logger/Logger.h"
#include "Types/Color/Color.h"
#include "Types/Effect/Effect.h"
#include "Types/Gradient.h"

AsyncWebSocket *ws = new AsyncWebSocket("/api/ws");

AsyncWebSocket *ControllerWS::WebSocket()
{
  return ws;
}

uint64_t lastMessage = 0;

void ControllerWS::handleWebSocketMessage(uint8_t *data, size_t len, AsyncWebSocketClient *sender)
{
  if (millis() - lastMessage < 35)
    return;
  lastMessage = millis();

  DynamicJsonDocument doc(3072); // Worst case with custom effect with 20 elements

  DeserializationError error = deserializeJson(doc, data, len);

  if (error)
    return Logger::error("deserializeJson() failed: " + String(error.c_str()));

  broadcastExcludingSender(doc.as<String>(), sender->id());

  const char *event = doc["event"];

  if (String(event) == "color")
  {
    JsonObject jsonData = doc["data"];
    LedManager::setColor(Color(jsonData));
  }
  else if (String(event) == "gradient")
  {
    JsonArray jsonArray = doc["data"];
    Gradient *gradient = new Gradient(jsonArray);
    // doc.clear();
    LedManager::setGradient(gradient);
  }
  // else if (String(event)=="effect") LedManager::setColor(Color(jsonData));
}

void ControllerWS::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                           void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
#ifdef DEVELOPMENT
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
#endif

  case WS_EVT_DATA:
    handleWebSocketMessage(data, len, client);
    break;
  }
}

void ControllerWS::setup()
{
  ws->onEvent(onEvent);
}

void ControllerWS::registerWebSocket(AsyncWebServer &server)
{
  setup();
  server.addHandler(ws);
}

void ControllerWS::broadcastExcludingSender(String message, uint16_t senderId)
{
  for (const auto &c : ws->getClients())
  {
    if (c->status() == WS_CONNECTED && c->id() != senderId)
      c->text(message);
  }
}