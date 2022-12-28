#include <ArduinoJson.h>

#include "SettingsManager.h"
#include "Logger/Logger.h"

#include <FS.h>
#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif 

SettingsManager* settingsManagerInstance = nullptr;

void SettingsManager::setup(){
  wifiSSID = nullptr;
  wifiPassword = nullptr;
  lastColor = nullptr;
  lastEffect = nullptr;

  getSettingsFromFile();

  setDefaults();
}

void SettingsManager::setDefaults(){
  if (!lastColor){
    lastColor = new Color();
    lastColor->r = 0;
    lastColor->g = 255;
    lastColor->b = 100;
  }

  if (!lastEffect) lastEffect = new String("C");
}

void SettingsManager::getSettingsFromFile(){
  Serial.println(SPIFFS.exists(CONFIG_FILENAME));
  if (!SPIFFS.exists(CONFIG_FILENAME)) return;
  
  String configJson = SPIFFS.open(CONFIG_FILENAME).readString();
  StaticJsonDocument<256> doc;

  DeserializationError err = deserializeJson(doc,configJson);

  if (err){
    Logger::error(err.f_str());
    return;
  }

  this->testJsonRead();

  const char* SSID = doc["SSID"];
  const char* PWD = doc["PWD"];
  const char* effect = doc["effect"];
  
  this->wifiSSID = new String(SSID);
  this->wifiPassword = new String(PWD);
  this->lastEffect = new String(effect);

  if (this->lastColor) delete this->lastColor;
  
  this->lastColor= new Color();
  JsonObject color = doc["color"];

  this->lastColor->r = color["r"]; 
  this->lastColor->g = color["g"]; 
  this->lastColor->b = color["b"]; 
  
  this->testJsonRead();
}

void SettingsManager::saveSettingsToFile(){
  File configFile = SPIFFS.open(CONFIG_FILENAME,"w",true);
  StaticJsonDocument<256> doc;

  doc["SSID"] = this->wifiSSID->c_str();
  doc["PWD"] = this->wifiPassword->c_str();
  doc["color"]["r"] = this->lastColor->r;
  doc["color"]["g"] = this->lastColor->g;
  doc["color"]["b"] = this->lastColor->b;
  doc["effect"] = this->lastEffect->c_str();

  String output = "";

  serializeJson(doc,output);

  Logger::log(output);
  configFile.print(output);

  configFile.close();
}

void SettingsManager::testJsonRead(){
  if (this->wifiSSID) Serial.println(*this->wifiSSID);
  if (this->wifiPassword) Serial.println(*this->wifiPassword);
  if (this->lastColor){
    Serial.println(this->lastColor->r);
    Serial.println(this->lastColor->g);
    Serial.println(this->lastColor->b);
  }
  if (this->lastEffect) Serial.println(*this->lastEffect);
}

SettingsManager& SettingsManager::getInstance(){
  if (!settingsManagerInstance) settingsManagerInstance = new SettingsManager;

  return *settingsManagerInstance;
}
