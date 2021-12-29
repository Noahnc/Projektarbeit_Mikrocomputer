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
        Serial.println();
        Serial.print("Connecting to wifi...");
        Serial.println(SSID);
        WiFi.begin(SSID, Password);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(50);
        }

        Serial.println("");
        Serial.println("Wifi Connected");
    }

