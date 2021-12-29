#ifndef MQTT_Callback_h
#define MQTT_Callback_h

#include "Arduino.h"

class MQTT_Callback
{

private:
    static bool Debug;

public:
    // static void init(bool debug);
    static void callback(char *topic, byte *message, unsigned int length);
};

#endif