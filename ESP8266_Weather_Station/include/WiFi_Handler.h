#pragma once
#include <ESP8266WiFi.h>

class WiFi_Handler
{
private:
    String SSID;
    String Password;

public:
    WiFi_Handler(String ssid, String pw);
    void init();
};
