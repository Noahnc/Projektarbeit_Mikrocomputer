#include <Arduino.h>
#include "RGB_LED_Handler.h"
#include "00config.h"

using namespace config_constants;

RGB_LED_Handler::RGB_LED_Handler(int blue, int green, int red)
{
    led_blue = blue;
    led_green = green;
    led_red = red;

    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_blue, OUTPUT);
}

void RGB_LED_Handler::SetLedColor(String HexValue)
{

    int number = (int)strtol(&HexValue[0], NULL, 16);
    red_value = number >> 16;
    green_value = number >> 8 & 0xFF;
    blue_value = number & 0xFF;

    if (debug_mode)
    {
        Serial.println("Change Red to " + String(red_value));
        Serial.println("Change Green to " + String(green_value));
        Serial.println("Change Blue to " + String(blue_value));
    }

    if (On)
    {
        analogWrite(led_red, red_value);
        analogWrite(led_green, green_value);
        analogWrite(led_blue, blue_value);
    }
}

void RGB_LED_Handler::TurnOnLED()
{
    if (red_value == 0 and green_value == 0 and blue_value == 0)
    {
        SetLedColor("062ff9");
    }

    if (debug_mode)
    {
        Serial.println("Turn LED On");
        Serial.println("Red = " + String(red_value));
        Serial.println("Green = " + String(green_value));
        Serial.println("Blue = " + String(blue_value));
    }

    analogWrite(led_red, red_value);
    analogWrite(led_green, green_value);
    analogWrite(led_blue, blue_value);
    On = true;
}

void RGB_LED_Handler::TurnOffLed()
{
    if (debug_mode)
    {
        Serial.println("Turn LED Off");
    }

    analogWrite(led_red, 0);
    analogWrite(led_green, 0);
    analogWrite(led_blue, 0);
    On = false;
}

bool RGB_LED_Handler::getLEDStatus(){
    return On;
}
