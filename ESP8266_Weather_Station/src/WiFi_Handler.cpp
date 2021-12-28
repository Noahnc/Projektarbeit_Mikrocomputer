#include <ESP8266WiFi.h>

class WiFi_Handler
{
private:
String SSID;
String Password;

public:
    WiFi_Handler(String ssid, String pw)
    {
        SSID = ssid;
        Password = pw;

    }
    void init()
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
};
