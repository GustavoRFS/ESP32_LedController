#include <Update.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>

#include "UpdateService.h"
#include "Utils/Utils.h"
#include "Controllers/ControllerWS/ControllerWS.h"

#include "definitions.h"

#ifdef USE_LITTLEFS
#define SPIFFS LITTLEFS
#include <LITTLEFS.h>
#else
#include <SPIFFS.h>
#endif

bool *hasUpdates = NULL;

void UpdateService::setup()
{
  xTaskCreate([](void *params)
              {
    uint64_t startTaskMillis = millis();
    while(!WiFi.isConnected() || startTaskMillis+5000 < millis());

    if (!SPIFFS.exists("/update.lck")) vTaskDelete(NULL);
    
    File updateLock = SPIFFS.open("/update.lck");
    String updateVersion = updateLock.readString();

    bool firmwareUpdateSuccess = updateVersion == VERSION;

    if (firmwareUpdateSuccess && UpdateService::downloadAssets()) SPIFFS.remove("/update.lck");
    
    vTaskDelete(NULL); },
              "Setup Updates", 12000, NULL, 1, NULL);
}

bool UpdateService::checkForUpdate()
{
  if (hasUpdates != NULL)
    return *hasUpdates;

  HTTPClient http;

  http.useHTTP10(true);
  http.begin(GITHUB_REPO_RELEASES_URL);

  int code = http.GET();

  if (code != 200)
    return false;

  StaticJsonDocument<80> filter;
  JsonObject filter_0 = filter.createNestedObject();

  filter_0["tag_name"] = true;

  StaticJsonDocument<256> doc;

  deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));

  http.end();

  if (doc.size() == 0)
  {
    hasUpdates = new bool(false);
    return *hasUpdates;
  }

  hasUpdates = new bool(doc[0]["tag_name"] != VERSION);

  return *hasUpdates;
}

Assets *UpdateService::getAllUpdateAssets(bool includeFirmware = true)
{
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(GITHUB_REPO_RELEASES_URL);

  int code = http.GET();

  if (code != 200)
    return new Assets();

  StaticJsonDocument<80> filter;
  JsonObject filter_0 = filter.createNestedObject();

  filter_0["assets"][0]["browser_download_url"] = true;
  filter_0["assets"][0]["name"] = true;

  StaticJsonDocument<4096> doc;

  deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));

  JsonArray newVersionAssets = doc[0]["assets"];

  Assets *assets = new Assets(newVersionAssets, includeFirmware);

  return assets;
}

void UpdateService::update()
{
  Assets *assets = getAllUpdateAssets();
  xTaskCreate([](void *params)
              {
    Assets* assets = (Assets*) params;

    File updateLock = SPIFFS.open("/update.lck","w",true);
    updateLock.print(VERSION);
    updateLock.close();

    String assetUrl = "";

    for (uint8_t i=0;i<assets->size;i++) {
      if (assets->assets[i].name=="firmware.bin") assetUrl = assets->assets[i].url;
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

      if (sendMessage) ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"firmware\",\"percentage\":"+String((float(total-remaining)/total)*100)+"}}");
    });

    Update.end(true);

    if (Update.hasError()){
      ws->textAll("{\"event\":\"updateError\",\"data\":\"Erro: " + String(Update.errorString())+"\"}");
    }
    else {
      ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"firmware\",\"percentage\":100}}");
      Utils::delay(500);
      ESP.restart();
    }

    delete assets;

    vTaskDelete(NULL); },
              "Download assets", 10000, (void *)assets, 1, NULL);
}

bool UpdateService::downloadAssets()
{
  Assets *assets = getAllUpdateAssets(false);

  if (assets->size == 0)
    return false;

  xTaskCreate([](void *params)
              {
    Assets* assets = (Assets*) params;

    for (uint8_t i=0;i<assets->size;i++) {
      Utils::downloadFile(assets->assets[i].url,assets->assets[i].name);
    }

    delete assets;
    vTaskDelete(NULL); },
              "UpdateService::downloadAssets", 9000, (void *)assets, 1, NULL);

  return true;
}