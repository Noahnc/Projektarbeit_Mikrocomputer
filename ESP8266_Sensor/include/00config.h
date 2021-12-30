#pragma once

namespace config_constants
{
    // WiFi Config
    const String wifi_ssid = "Demo";
    const String wifi_wpa_psk = "Demo2021735bd";

    // MQTT Server
    const String mosquito_server = "raspberrypi-noah.local";

    // Debug Mode (gibt diverse Informationen per Serial aus)
    const bool debug_mode = false;

    // Intervall in Sekunden, in welchm der Sensor gelesen und die Daten übermittelt werden.
    const int sensor_interval = 30;

    // RGB LED pins
    static const int led_red = 15;
    static const int led_green = 13;
    static const int led_blue = 12;

}
