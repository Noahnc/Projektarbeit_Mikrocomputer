#include <ESP8266WiFi.h>
#include "WiFi_Handler.h"
#include <Arduino.h>
#include "00config.h"
#include <string>
#include <IPAddress.h>

using namespace config_constants;

WiFi_Handler::WiFi_Handler(String ssid, String pw)
{
    SSID = ssid;
    Password = pw;
}
void WiFi_Handler::init()
{
    if (debug_mode)
    {
        Serial.println();
        Serial.print("Connecting to SSID: " + SSID);
    }
    WiFi.begin(SSID, Password);

    while (WiFi.status() != WL_CONNECTED)
    {
        if (debug_mode)
        {
            Serial.print(".");
        }
        delay(50);
    }
    if (debug_mode)
    {
        Serial.println("");
        Serial.println("SSID " + SSID + " connected");
    }
}
String WiFi_Handler::getNetworkiP()
{
    IPAddress ip = WiFi.localIP();
    String s = "";
    for (int i = 0; i < 4; i++)
        s += i ? "." + String(ip[i]) : String(ip[i]);
    return s;
}

String WiFi_Handler::getConnectedSSID()
{
    return SSID;
}

String WiFi_Handler::getWiFiRSSI()
{

    return String(WiFi.RSSI());
}

String WiFi_Handler::getHostname()
{
    return WiFi.hostname();
}
