#pragma once

class WifiManager{
  public:
    static void setup();
    static void connect(String ssid, String password);
    static void enableAP();
    static void disableAP();
    static void beginMDNS();
};
