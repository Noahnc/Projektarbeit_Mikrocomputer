#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "mqtt_topics.h"
#include "RGB_LED_Handler.h"
#include <string>
#include <Arduino.h>
#include "MQTT_Handler.h"
#include "MQTT_Callback.h"

MQTT_Handler::MQTT_Handler(String server)
{
    Server = (char *)server.c_str();
}
void MQTT_Handler::init()
{
    client.setClient(espClient);
    Serial.print("Connecting to mqtt...");
    client.setServer(Server, 1883);
    client.setCallback(MQTT_Callback::callback);
}

void MQTT_Handler::reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attemping MQTT connection...");

        String clientId = "ESP8266-";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str()))
        {
            Serial.print("Connecting to mqtt topics...");
            client.connect(temp_topic);
            client.connect(humidity_topic);
            client.connect(preassure_topic);
            client.connect(gas_topic);

            client.subscribe(rgb_topic);
            client.subscribe(rgb_switch_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");

            delay(5000);
        }
    }
}

bool MQTT_Handler::CheckConnection()
{
    // Mqtt
    if (!client.connected())
    {
        Serial.println("MQTT not connected. Reconnecting...");
        return false;
    }
    else
    {
        return true;
    }
}

void MQTT_Handler::SendData(char *topic, String Data)
{
    client.publish(topic, (char *)Data.c_str());
}
