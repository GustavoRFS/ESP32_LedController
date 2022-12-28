#include <ESPAsyncWebServer.h>

class ControllerWS{
  public:
    static AsyncWebSocket* WebSocket();
    static void registerWebSocket(AsyncWebServer& server);
  private:
    static void setup();
    static void handleWebSocketMessage( uint8_t *data, size_t len);
    static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                        void *arg, uint8_t *data, size_t len);
};