#pragma once
#include <HTTPClient.h>
class Utils{
  public:
    static void saveFileFromStream(HTTPClient& client,String filename, String message);
    static String getDownloadURL(String url);
    static void delay(uint64_t milliseconds);
    static void downloadFile(String url,String fileName,String message);
    static String listDirectories(String dirname, uint8_t levels);
    template<typename Func> static void handleStream(HTTPClient& client,Func callback){
      int total = client.getSize();
      int remaining = total;

      int BUFF_SIZE = 1024;

      uint8_t buff[BUFF_SIZE] = { 0 };
      WiFiClient * stream = client.getStreamPtr();


      while (client.connected())
      {
        int bytesToRead = remaining > BUFF_SIZE ? BUFF_SIZE:remaining;

        stream->readBytes(buff,bytesToRead);

        callback(buff,bytesToRead, remaining, total);

        remaining -= BUFF_SIZE;
      }
    }
    template<typename Func> static void scheduleRoutineTask(Func task,uint64_t intervalMilliseconds,uint32_t stackDepth=1000,UBaseType_t priority=1){
      xTaskCreate([task,intervalMilliseconds](void* params){
        while(true){
          task();
          Utils::delay(intervalMilliseconds);
        }
      },
      "scheduleRoutineTask",
      stackDepth,
      NULL,
      priority,
      NULL);
    }
};