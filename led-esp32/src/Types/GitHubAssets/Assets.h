#pragma once
#include <ArduinoJson.h>

#include "AssetMetadata.h"

class Assets{
  public:
    int size;
    AssetMetadata* assets;
    Assets(){
      size=0;
      assets=NULL;
    }  
    Assets(JsonArray doc,bool includeFirmware=true){
      size=doc.size();
      if (!includeFirmware) size--;
      
      assets = new AssetMetadata[size];

      uint8_t assetsCounter=0;
      for (uint8_t i=0;i<doc.size();i++){
        String url = doc[i]["browser_download_url"].as<String>();
        String name = doc[i]["name"].as<String>();
        
        bool shouldNotAddToAssets = !includeFirmware && name=="firmware.bin";

        if (!shouldNotAddToAssets) {
          assets[assetsCounter] = AssetMetadata(url,name);
          assetsCounter++;
        }
      }
    }
    ~Assets(){
      if (assets)delete[] assets;
    }
};