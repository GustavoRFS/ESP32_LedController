#include <WiFi.h>
#include <ESPmDNS.h>

#include "WifiManager.h"
#include "Logger/Logger.h"
#include "SettingsManager/SettingsManager.h"
#include "ControllerWS/ControllerWS.h"

void WifiManager::setup(){
  WiFi.onEvent([](arduino_event_id_t event){
    Logger::log(String(event));

    Logger::log(WiFi.localIP().toString());

    WifiManager::beginMDNS();
  });

  SettingsManager settings = SettingsManager::getInstance();

  String* ssid = settings.wifiSSID;
  String* password = settings.wifiPassword;

  if (!ssid){
    WifiManager::enableAP();
    return;
  }

  if (!password){
    password = new String("");
  }
  
  WifiManager::connect(*ssid,*password);
}

void WifiManager::connect(String ssid, String password){
  WiFi.begin(ssid.c_str(),password.c_str()); 

  WiFi.onEvent([](arduino_event_id_t event){
    WifiManager::enableAP();

    WiFi.removeEvent(ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  },ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.onEvent([](arduino_event_id_t event){
    WifiManager::beginMDNS();
    ControllerWS::WebSocket()->textAll("wifi-connected");
    
    delay(2000);
    
    WifiManager::disableAP();

    WiFi.removeEvent(ARDUINO_EVENT_WIFI_STA_CONNECTED);
  },ARDUINO_EVENT_WIFI_STA_CONNECTED);
}

void WifiManager::enableAP(){
  WiFi.softAP("PP's LED");
  WiFi.enableAP(true);

  WiFi.onEvent([](arduino_event_id_t event){
    WifiManager::beginMDNS();

    WiFi.removeEvent(ARDUINO_EVENT_WIFI_AP_START);
  },ARDUINO_EVENT_WIFI_AP_START);

  Logger::log(WiFi.broadcastIP().toString());
  Logger::log(WiFi.gatewayIP().toString());
}

void WifiManager::disableAP(){
  WiFi.enableAP(false);
}

void WifiManager::beginMDNS(){
  MDNS.end();
  MDNS.begin("pp");
}
