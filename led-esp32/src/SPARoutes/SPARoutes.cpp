#include "SPARoutes.h"

#include <FS.h>
#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif


void SPARoutes::registerRoutes(AsyncWebServer &server){
  server.on("/*", HTTP_GET, [&](AsyncWebServerRequest *request){
    String url = request->url();

    if (url.endsWith(".js")){
      url="index.js";
    }
    else if (url.endsWith(".css")){
      url="index.css";
    }
    else if (url.endsWith(".svg")){
      url="index.svg";
    }else{
      url="index.html";
    }
    
    request->send(SPIFFS, "/web/"+url);
  }); 
}
