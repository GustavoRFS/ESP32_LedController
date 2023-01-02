#include <HTTPClient.h>


class Utils{
  public:
    static void saveFileFromStream(HTTPClient& client,String filename);
    static String getDownloadURL(String url);
    static void downloadFile(String url,String fileName);
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
};