#include "SPARoutes.h"

#include "definitions.h"

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

    url.replace("/assets","");

    if (url=="/" || !SPIFFS.exists(url)) url="/index.html";
    
    request->send(SPIFFS, url);
  }); 
}
