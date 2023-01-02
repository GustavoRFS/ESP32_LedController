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
    Assets(JsonArray doc){
      size=doc.size();
      Serial.println(size);
      assets = new AssetMetadata[size];
      for (uint8_t i=0;i<doc.size();i++){
        String url = doc[i][F("browser_download_url")].as<String>();
        String name = doc[i][F("name")].as<String>();
        
        assets[i] = AssetMetadata(url,name);
      }
    }
};