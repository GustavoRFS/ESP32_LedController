#include <Update.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "UpdateService.h"
#include "definitions.h"

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

void UpdateService::update(){
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(F(GITHUB_REPO_RELEASES_URL));

  int code = http.GET();

  if (code != 200) return;

  StaticJsonDocument<80> filter;
  JsonObject filter_0 = filter.createNestedObject();

  filter_0["assets"][0]["browser_download_url"] = true;

  StaticJsonDocument<512> doc;

  deserializeJson(doc,http.getStream(),DeserializationOption::Filter(filter));

  JsonArray newVersionAssets = doc[0][F("assets")];

  for (uint16_t i=0;i<newVersionAssets.size();i++){
    String assetUrl = newVersionAssets[i]["browser_download_url"].as<String>();

    Serial.println(assetUrl);
  }
}