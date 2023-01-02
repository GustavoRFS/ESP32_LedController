#include <Update.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>

#include "UpdateService.h"
#include "definitions.h"
#include "Utils/Utils.h"
#include "ControllerWS/ControllerWS.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif

void updateFirmware(void* params){
  Assets* assets = (Assets*) params;

  File updateLock = SPIFFS.open("/update.lck","w",true);
  updateLock.println(VERSION);
  updateLock.close();

  String assetUrl = "";

  for (uint8_t i=0;i<assets->size;i++) {
    if (assets->assets[i].name.endsWith(".bin")) assetUrl = assets->assets[i].url;
  }

  if (!Update.begin(UPDATE_SIZE_UNKNOWN)){
    Update.printError(Serial);
  }

  String downloadURL=Utils::getDownloadURL(assetUrl);

  HTTPClient http;

  http.begin(downloadURL);
  http.useHTTP10(true);
  int code = http.GET();

  if (code!=200) return;

  AsyncWebSocket* ws = ControllerWS::WebSocket();

  bool sendMessage = ws->count()>0;

  Utils::handleStream(http,[sendMessage,ws](uint8_t* buff,size_t size,size_t remaining,size_t total){
    Update.write(buff,size);

    if (sendMessage) ws->textAll("Baixando firmware: "+String((float(total-remaining)/total)*100)+"%");

    Serial.println("Baixando firmware: "+String((float(total-remaining)/total)*100)+"%");
  });

  Serial.println("Fim do stream");

  Update.end();

  if (Update.hasError()){
    ws->textAll("Erro: " + String(Update.errorString()));
  }
  else ESP.restart();

  vTaskDelete(NULL);
}

void downloadAssets(void* params){
  Assets* assets = (Assets*) params;
  for (uint8_t i=0;i<assets->size;i++) {
    if (!assets->assets[i].name.endsWith(".bin")) Utils::downloadFile(assets->assets[i].url,assets->assets[i].name);
    Serial.println(assets->assets[i].url+" "+assets->assets[i].name);
  }
  vTaskDelete(NULL);
}

void UpdateService::setup(){
  if (!SPIFFS.exists("update.lck")) return;

  File updateLock = SPIFFS.open("update.lck");

  String updateVersion = updateLock.readString();

  bool firmwareUpdateSuccess = updateVersion == VERSION;

  if (firmwareUpdateSuccess) UpdateService::downloadUpdateAssets();
}

bool UpdateService::checkForUpdate(){
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(F(GITHUB_REPO_RELEASES_URL));

  int code = http.GET();

  if (code != 200) return false;

  StaticJsonDocument<80> filter;
  JsonObject filter_0 = filter.createNestedObject();

  filter_0[F("tag_name")] = true;

  StaticJsonDocument<256> doc;

  deserializeJson(doc,http.getStream(),DeserializationOption::Filter(filter));

  http.end();

  return doc[0][F("tag_name")] != VERSION; 
}

Assets UpdateService::getAllUpdateAssets(){
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(F(GITHUB_REPO_RELEASES_URL));

  int code = http.GET();

  if (code != 200) return Assets();

  StaticJsonDocument<80> filter;
  JsonObject filter_0 = filter.createNestedObject();

  filter_0["assets"][0]["browser_download_url"] = true;
  filter_0["assets"][0]["name"] = true;

  StaticJsonDocument<2048> doc;

  deserializeJson(doc,http.getStream(),DeserializationOption::Filter(filter));

  JsonArray newVersionAssets = doc[0][F("assets")];

  Assets assets = Assets(newVersionAssets);

  doc.clear();

  return assets;
}

void UpdateService::update(){
  Assets assets = getAllUpdateAssets();
  xTaskCreate(updateFirmware,"Download assets",10000,(void*)&assets,1,NULL);
}

void UpdateService::downloadUpdateAssets(){
  Assets assets = getAllUpdateAssets();
  xTaskCreate(downloadAssets,"Download assets",10000,(void*)&assets,1,NULL);
}