#ifndef MQTT_Handler_h
#define MQTT_Handler_h

#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "RGB_LED_Handler.h"
#include <string>
#include <Arduino.h>
#include <00config.h>

class MQTT_Handler
{
private:
    String MQTT_Server;
    const char *Server;
    WiFiClient espClient;
    PubSubClient client;
    String clientId = "ESP8266-" + String(random(0xffff), HEX);

public:
    static RGB_LED_Handler LED;
    MQTT_Handler(String server);
    void init();
    void reconnect();
    bool CheckConnection();
    void SendData(char const *topic, String Data);
    static void callback(char *topic, byte *message, unsigned int length);
    void ReadIncoming();
};

#endif