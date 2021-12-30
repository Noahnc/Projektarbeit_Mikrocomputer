#ifndef WiFi_Handler_h
#define WiFi_Handler_h

#include <ESP8266WiFi.h>
#include "WiFi_Handler.h"
#include <Arduino.h>

class WiFi_Handler
{
private:
    String SSID;
    String Password;

public:
    WiFi_Handler(String, String);
    void init();
    String getNetworkiP();
    String getConnectedSSID();
    String getWiFiRSSI();
    String getHostname();
};


#endif



