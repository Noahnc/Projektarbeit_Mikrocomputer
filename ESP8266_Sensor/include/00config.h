#pragma once

namespace config_constants
{
    // WiFi SSID
    const String wifi_ssid = "Cananet ";

    const String wifi_wpa_psk = "pw";

    // MQTT Server
    const String mqtt_server = "raspberrypi-noah.local";

    // Debug Mode (gibt diverse Informationen per Serial aus)
    const bool debug_mode = true;

    // RGB LED pins
    static const int led_red = 15;
    static const int led_green = 13;
    static const int led_blue = 12;

}
