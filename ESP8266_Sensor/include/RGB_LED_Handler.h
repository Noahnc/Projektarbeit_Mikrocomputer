#ifndef RGB_LED_Handler_h
#define RGB_LED_Handler_h

#include <Arduino.h>


class RGB_LED_Handler
{
private:
    int led_red;
    int led_green;
    int led_blue;
    int red_value;
    int green_value;
    int blue_value;

public:
    RGB_LED_Handler(int blue, int green, int red);
    void SetLedColor(String HexValue);
    void TurnOnLED();
    void TurnOffLed();

};

#endif



