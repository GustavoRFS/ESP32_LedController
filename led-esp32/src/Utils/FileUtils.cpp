#include "Utils.h"
#include "definitions.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif

void Utils::saveFileFromString(String data,String filePath){
  File file = SPIFFS.open(filePath,"w",true);

  file.print(data);

  file.close();
}