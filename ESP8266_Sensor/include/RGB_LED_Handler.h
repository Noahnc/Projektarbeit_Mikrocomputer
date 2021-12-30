#ifndef RGB_LED_Handler_h
#define RGB_LED_Handler_h

#include <Arduino.h>


class RGB_LED_Handler
{
private:
    int led_red;
    int led_green;
    int led_blue;
    int red_value = 0;
    int green_value = 0;
    int blue_value = 0;
    bool On;

public:
    RGB_LED_Handler(int blue, int green, int red);
    void SetLedColor(String HexValue);
    void TurnOnLED();
    void TurnOffLed();
    bool getLEDStatus();

};

#endif



