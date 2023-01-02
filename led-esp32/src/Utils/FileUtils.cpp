#include "Utils.h"
#include "definitions.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif

void Utils::saveFileFromStream(HTTPClient& client,String filePath){
  File file = SPIFFS.open(filePath,"w",true);

  handleStream(client,[&file](uint8_t* buff,size_t size,size_t remaining,size_t total){
    file.write(buff,size);
    Serial.println(remaining);
  });

  Serial.println(filePath+" finished");

  file.close();
}