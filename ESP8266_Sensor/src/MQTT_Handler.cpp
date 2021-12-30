#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "RGB_LED_Handler.h"
#include <string>
#include <Arduino.h>
#include "MQTT_Handler.h"
#include "00config.h"
#include "01mqtt_topics.h"

using namespace config_constants;

MQTT_Handler::MQTT_Handler(String server)
{
    MQTT_Server = server;
}

void MQTT_Handler::init()
{
    client.setClient(espClient);
    client.setServer(MQTT_Server.c_str(), 1883);
    client.setCallback(callback);
    if (debug_mode)
    {
        Serial.print("Connecting to MQTT Server: ");
        Serial.println(MQTT_Server);
    }
}

void MQTT_Handler::reconnect()
{
    while (!client.connected())
    {
        if (client.connect(clientId.c_str()))
        {
            if (debug_mode)
            {
                Serial.print("Connecting to MQTT topics: ");
            }
            client.connect(ESP_JSON_DATA);

            client.subscribe(rgb_topic);
            client.subscribe(rgb_switch_topic);

            if (debug_mode)
            {
                Serial.println("OK");
            }
        }
        else
        {
            if (debug_mode)
            {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.print(" Server=");
                Serial.print(MQTT_Server);
                Serial.print(", Client=");
                Serial.print(clientId);
                Serial.println(" try again in 5 seconds");
            }

            delay(5000);
        }
    }
}

bool MQTT_Handler::CheckConnection()
{
    // Mqtt
    if (!client.connected())
    {
        if (debug_mode)
        {
            Serial.println("MQTT not connected. Reconnecting...");
        }
        return false;
    }
    else
    {
        return true;
    }
}

void MQTT_Handler::SendData(char const *topic, String Data)
{
    client.publish(topic, (char *)Data.c_str());
}

void MQTT_Handler::ReadIncoming()
{
    client.loop();
}

void MQTT_Handler::callback(char *topic, byte *message, unsigned int length)
{
    // Erstellen der LED
    static RGB_LED_Handler LED = RGB_LED_Handler(led_blue, led_green, led_red);

    if (debug_mode)
    {
        Serial.println();
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
    }

    String messageTemp;
    for (int i = 0; i < length; i++)
    {
        if (debug_mode)
        {
            Serial.print((char)message[i]);
        }

        messageTemp += (char)message[i];
    }

    if (debug_mode)
    {
        Serial.println();
    }

    if (String(topic) == rgb_topic)
    {
        if (debug_mode)
        {
            Serial.println(messageTemp);
            Serial.println("Changing led rgb value:");
        }

        LED.SetLedColor(messageTemp);
    }
    else if (String(topic) == rgb_switch_topic)
    {
        if (debug_mode)
        {
            Serial.println(messageTemp);
            Serial.println("Changing led on off state:");
        }

        if (messageTemp == "true")
        {
            LED.TurnOnLED();
        }
        else
        {
            LED.TurnOffLed();
        }
    }
}
