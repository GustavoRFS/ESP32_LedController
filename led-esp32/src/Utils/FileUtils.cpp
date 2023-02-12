#include "Utils.h"
#include "Controllers/ControllerWS/ControllerWS.h"

#include "definitions.h"

#ifdef USE_LITTLEFS
#define SPIFFS LITTLEFS
#include <LITTLEFS.h>
#else
#include <SPIFFS.h>
#endif

#ifdef DEVELOPMENT
String Utils::listDirectories(String dirname, uint8_t levels)
{
  File root = SPIFFS.open("/");

  File file = root.openNextFile();

  String response = "";

  while (file)
  {
    response += "File: ";
    response += file.name();
    response += "\n";

    file = root.openNextFile();
  }

  return response;
}
#endif

void Utils::saveFileFromStream(HTTPClient &client, String filePath)
{
  File file = SPIFFS.open(filePath, "w", true);

  AsyncWebSocket *ws = ControllerWS::WebSocket();

  handleStream(client, [&file, ws, filePath](uint8_t *buff, size_t size, size_t remaining, size_t total)
               {
    file.write(buff,size);
    ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"" + filePath +"\",\"percentage\":" + String((float(total - remaining) / total) * 100) + "}}"); });

  file.close();
  ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"" + filePath + "\",\"percentage\":100}}");
}

void Utils::rmOldVersionDir()
{
  File root = SPIFFS.open("/");

  File file = root.openNextFile();

  while (file)
  {
    if (file.name() != VERSION && file.isDirectory())
    {
      SPIFFS.rmdir(file.name());
    }
    file = root.openNextFile();
  }
}