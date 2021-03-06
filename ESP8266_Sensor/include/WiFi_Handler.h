#ifndef WiFi_Handler_h
#define WiFi_Handler_h

#include <ESP8266WiFi.h>
#include "WiFi_Handler.h"
#include <Arduino.h>
#include "NTPClient.h"
#include <WiFiUdp.h>

class WiFi_Handler
{
private:
    String SSID;
    String Password;
    String Hostname;
    String NTP_server;


public:
    WiFi_Handler(String ssid, String pw, String hostname);
    void init();
    String getNetworkiP();
    String getConnectedSSID();
    int getWiFiRSSI();
    String getHostname();
    bool CheckWiFiConnected();

};

#endif
