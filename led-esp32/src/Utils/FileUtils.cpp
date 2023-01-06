#include "Utils.h"
#include "ControllerWS/ControllerWS.h"

#include "definitions.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif

#ifdef DEVELOPMENT
String Utils::listDirectories(String dirname, uint8_t levels){
  String dirs = "";
  dirs += "Listing directory: "+ dirname + "\r\n";

  File root = SPIFFS.open(dirname);
  
  if(!root){
      dirs +="- failed to open directory";
      return dirs;
  }

  if(!root.isDirectory()){
      dirs += " - not a directory";
      return dirs;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      dirs+="  DIR : ";
      dirs+=file.name();
      if(levels){    
          dirs+=listDirectories(file.path(), levels -1);
      }
    } else {
      dirs+="  FILE: ";
      dirs+=file.name();
      dirs+="\tSIZE: ";
      dirs+=file.size();
    }
    file = root.openNextFile();
  }
}
#endif


void Utils::saveFileFromStream(HTTPClient& client,String filePath,String message){
  File file = SPIFFS.open(filePath,"w",true);

  AsyncWebSocket* ws = ControllerWS::WebSocket();

  handleStream(client,[&file,ws,filePath,message](uint8_t* buff,size_t size,size_t remaining,size_t total){
    file.write(buff,size);
    ws->textAll("Baixando "+filePath+" "+ String((float(total-remaining)/total)*100)+"%\n"+message);
  });

  file.close();

  ws->textAll("Baixando "+filePath+" 100%\n"+message);
}