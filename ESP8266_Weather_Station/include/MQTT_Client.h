#pragma once
#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "mqtt_topics.h"
#include "RGB_LED_Handler.h"
#include <string>

class MQTT_Client
{
private:
    char* Server;
    WiFiClient espClient;
    PubSubClient client;
    static RGB_LED_Handler* LED;

public:
    MQTT_Client(String server, RGB_LED_Handler* led);
    void init();
    void reconnect();
    bool CheckConnection();
    void SendData(char *topic, String Data);
};