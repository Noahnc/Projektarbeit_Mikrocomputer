#include <Arduino.h>
#include "RGB_LED_Handler.h"

RGB_LED_Handler::RGB_LED_Handler(int blue, int green, int red)
{
    led_blue = blue;
    led_green = green;
    led_red = red;
}

void RGB_LED_Handler::SetLedColor(String HexValue)
{

    int number = (int)strtol(&HexValue[0], NULL, 16);
    red_value = number >> 16;
    green_value = number >> 8 & 0xFF;
    blue_value = number & 0xFF;

    analogWrite(led_red, red_value);
    analogWrite(led_green, green_value);
    analogWrite(led_blue, blue_value);
}

void RGB_LED_Handler::TurnOnLED()
{
    if (red_value == 0 and green_value == 0 and blue_value == 0)
    {
        led_blue = 100;
        led_green = 100;
        led_red = 100;
    }

    analogWrite(led_red, red_value);
    analogWrite(led_green, green_value);
    analogWrite(led_blue, blue_value);
}

void RGB_LED_Handler::TurnOffLed()
{

    analogWrite(led_red, 0);
    analogWrite(led_green, 0);
    analogWrite(led_blue, 0);
}
