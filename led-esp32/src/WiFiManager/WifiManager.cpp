#include <WiFi.h>
#include <ESPmDNS.h>

#include "WifiManager.h"
#include "Logger/Logger.h"
#include "SettingsManager/SettingsManager.h"
#include "Controllers/ControllerWS/ControllerWS.h"
#include "UpdateService/UpdateService.h"
#include "Utils/Utils.h"

// Variables used to be saved at settings if connection is OK
String lastSSID;
String lastPWD;

uint64_t *lastDisconnectMillis = nullptr;

TaskHandle_t broadcastSSIDsTask = NULL;

void WifiManager::startSSIDsBroadcast()
{
  xTaskCreate([](void *params)
              {
    while (true)
    {
      AsyncWebSocket* ws = ControllerWS::WebSocket();

      if (ws->count()<=0){
        Utils::delay(1000);
        continue;
      }

      int n =WiFi.scanNetworks(false,true);

      String ssids = "[";

      for (int i = 0; i < n; ++i){
        if (i) ssids += ",";
        ssids += "{\"name\":\"" + WiFi.SSID(i) + "\",\"signal\":" + map(WiFi.RSSI(i),-100,-50,0,100) + "}";
      }
      WiFi.scanDelete();
      ssids += "]";

      ws->textAll("{\"event\":\"wifiScan\",\"data\":" + ssids + "}");

      Utils::delay(2000);
    } },
              "broadcastSSIDs",
              2000,
              nullptr,
              1, &broadcastSSIDsTask);
}

void WifiManager::stopSSIDsBroadcast()
{
  if (broadcastSSIDsTask != NULL)
    vTaskDelete(broadcastSSIDsTask);
}

void WifiManager::setup()
{
  WiFi.onEvent([](arduino_event_id_t event)
               {
    Logger::log(String(event));

    Logger::log(WiFi.localIP().toString());

    WifiManager::beginMDNS(); });

  SettingsManager *settings = SettingsManager::getInstance();

  String *ssid = settings->wifiSSID;
  String *password = settings->wifiPassword;

  if (!ssid)
  {
    WifiManager::startSSIDsBroadcast();
    WifiManager::enableAP();
    return;
  }

  if (!password)
  {
    password = new String();
  }

  WifiManager::connect(*ssid, *password);
}

void WifiManager::connect(String ssid, String password)
{
  lastSSID = ssid;
  lastPWD = password;

  WiFi.enableSTA(true);
  WiFi.begin(ssid.c_str(), password.c_str());

  WiFi.onEvent([](arduino_event_id_t event)
               {
    WiFi.removeEvent(ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    if (lastDisconnectMillis && *lastDisconnectMillis < millis() + 10000){
      WiFi.enableSTA(false);

      delete lastDisconnectMillis;
      lastDisconnectMillis = nullptr;
    }
    else if (!lastDisconnectMillis) lastDisconnectMillis = new uint64_t(millis());

    WifiManager::startSSIDsBroadcast();

    WifiManager::enableAP(); },
               ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.onEvent([](arduino_event_id_t event)
               {
    WifiManager::beginMDNS();
    ControllerWS::WebSocket()->textAll("{\"event\":\"wifiConnected\"}");
    SettingsManager::getInstance()->setWifi(lastSSID,lastPWD);

    WifiManager::stopSSIDsBroadcast();
    
    Utils::delay(2000);
    
    WifiManager::disableAP();
    
    WiFi.removeEvent(ARDUINO_EVENT_WIFI_STA_CONNECTED); },
               ARDUINO_EVENT_WIFI_STA_CONNECTED);
}

void WifiManager::enableAP()
{
  WiFi.softAP("PP's LED");
  WiFi.enableAP(true);

  WiFi.onEvent([](arduino_event_id_t event)
               {
    WifiManager::beginMDNS();

    WiFi.removeEvent(ARDUINO_EVENT_WIFI_AP_START); },
               ARDUINO_EVENT_WIFI_AP_START);

  Logger::log(WiFi.broadcastIP().toString());
  Logger::log(WiFi.gatewayIP().toString());
}

void WifiManager::disableAP()
{
  WiFi.enableAP(false);
}

void WifiManager::beginMDNS()
{
  MDNS.end();
  MDNS.begin("pp");
}
