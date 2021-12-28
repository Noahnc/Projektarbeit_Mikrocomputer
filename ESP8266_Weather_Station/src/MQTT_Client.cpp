#include <PubSubClient.h>
#include <iostream>
#include <ESP8266WiFi.h>
#include "mqtt_topics.h"
#include "RGB_LED_Handler.h"
#include <string>

class MQTT_Client
{
private:
    char *Server;
    WiFiClient espClient;
    PubSubClient client;
    static RGB_LED_Handler* LED;

public:
    MQTT_Client(String server, RGB_LED_Handler* led)
    {
        Server = (char *)server.c_str();
        LED = led;
    }
    void init()
    {
        client.setClient(espClient);
        Serial.print("Connecting to mqtt...");
        client.setServer(Server, 1883);
        client.setCallback(callback);
    }

    void reconnect()
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

    bool CheckConnection()
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

    void SendData(char *topic, String Data)
    {
        client.publish(topic, (char *)Data.c_str());
    }

    static void callback(char *topic, byte *message, unsigned int length)
    {
        Serial.println();
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");

        String messageTemp;
        for (int i = 0; i < length; i++)
        {
            Serial.print((char)message[i]);
            messageTemp += (char)message[i];
        }

        Serial.println();
        if (String(topic) == rgb_topic)
        {
            Serial.println(messageTemp);
            Serial.print("Changing led rgb value");

            LED->SetLedColor(messageTemp);
        }
        else if (String(topic) == rgb_switch_topic)
        {
            Serial.println(messageTemp);
            Serial.print("Changing led on off state");

            if (messageTemp == "true")
            {
                LED->TurnOnLED();
            }
            else
            {
                LED->TurnOffLed();
            }
        }
    }

};