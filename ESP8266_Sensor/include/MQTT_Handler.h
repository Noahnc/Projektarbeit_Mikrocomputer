#ifndef MQTT_Handler_h
#define MQTT_Handler_h

#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "mqtt_topics.h"
#include "RGB_LED_Handler.h"
#include <string>
#include <Arduino.h>


class MQTT_Handler
{
private:
    char *Server;
    WiFiClient espClient;
    PubSubClient client;
    static RGB_LED_Handler LED;

public:
    MQTT_Handler(String server);
    void init();
    void reconnect();
    bool CheckConnection();
    void SendData(char *topic, String Data);
}; 

#endif