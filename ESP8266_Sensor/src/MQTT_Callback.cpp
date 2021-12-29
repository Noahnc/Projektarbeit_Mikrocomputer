#include "Arduino.h"
#include "RGB_LED_Handler.h"
#include "mqtt_topics.h"
#include "MQTT_Callback.h"
#include "01LEDconfig.h"

/* void MQTT_Callback::init(bool debug){
    Debug = debug;
} */

void MQTT_Callback::callback(char *topic, byte *message, unsigned int length)
{
    // Erstellen der LED
    static RGB_LED_Handler LED = RGB_LED_Handler(led_blue, led_green, led_red);

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

        // LED.SetLedColor(messageTemp);
    }
    else if (String(topic) == rgb_switch_topic)
    {
        Serial.println(messageTemp);
        Serial.print("Changing led on off state");

        if (messageTemp == "true")
        {
            // LED.TurnOnLED();
        }
        else
        {
            // LED.TurnOffLed();
        }
    }
}