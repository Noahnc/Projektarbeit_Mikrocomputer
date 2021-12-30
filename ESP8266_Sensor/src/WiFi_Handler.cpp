#include <ESP8266WiFi.h>
#include "WiFi_Handler.h"
#include <Arduino.h>
#include "00config.h"

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
