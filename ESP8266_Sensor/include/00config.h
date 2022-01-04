/*
########################################################################
#                  Globale konfigurations variablen
########################################################################
#                           Description
#            In dieser Datei sind alle globalen Variablen
*/

#pragma once

namespace config_constants
{
    // Stationsname, muss gleich sein wie Name in SQL DB:
    const String ESP_Hostname = "ESP-Projektarbeit-Mikrocomputer";

    // WiFi Config:
    const String wifi_ssid = "Demo";
    const String wifi_wpa_psk = "Demo2021735bd";

    // NTP Server:
    const String NTP_Server = "ch.pool.ntp.org";

    // MQTT Server angaben:
    const String mosquitto_server = "projektarbeit-mikrocomputer.canadea.ch";
    const String mosquitto_user = "mqtt_user";
    const String mosquitto_pw = "jfjhHbhf86edjdjHG";

    // Debug Mode (gibt diverse Informationen per Serial aus)
    const bool debug_mode = false;

    // Intervall in Sekunden, in welchem Daten ausgewertet und per mqtt übermittelt werden.
    const int mqtt_update_interval = 30;

    // RGB LED pins
    static const int led_red = 15;
    static const int led_green = 13;
    static const int led_blue = 12;

    const char mosquitto_ca[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIEITCCAwmgAwIBAgIUZBHnAWXhUPcrX14szV+OC/5p3swwDQYJKoZIhvcNAQEL
BQAwgZ8xCzAJBgNVBAYTAkNIMRAwDgYDVQQIDAdadWVyaWNoMRAwDgYDVQQHDAda
dWVyaWNoMQ0wCwYDVQQKDARUZWtvMQswCQYDVQQLDAJJVDEvMC0GA1UEAwwmcHJv
amVrdGFyYmVpdC1taWtyb2NvbXB1dGVyLmNhbmFkZWEuY2gxHzAdBgkqhkiG9w0B
CQEWEGFkbWluQGNhbmFkZWEuY2gwHhcNMjExMjMxMTUzOTA2WhcNMzExMjI5MTUz
OTA2WjCBnzELMAkGA1UEBhMCQ0gxEDAOBgNVBAgMB1p1ZXJpY2gxEDAOBgNVBAcM
B1p1ZXJpY2gxDTALBgNVBAoMBFRla28xCzAJBgNVBAsMAklUMS8wLQYDVQQDDCZw
cm9qZWt0YXJiZWl0LW1pa3JvY29tcHV0ZXIuY2FuYWRlYS5jaDEfMB0GCSqGSIb3
DQEJARYQYWRtaW5AY2FuYWRlYS5jaDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC
AQoCggEBAPKndROA7oqYrZu/n3l27UO4750BXTDW3ToQv9JZ3r5yDAUYSrZ5IXI+
2WI20z9g87/j3iT+EUvQvoNCJUJxIvPuqTqDLV8kmarNbDBmAYWeJ2AKdH50PhRj
LLS95TADEguETjW7d6PNlfHsig7O04G0mSighbecCV/tl5jfUYkSRomOvC3IH0dF
j1AX5oOvqJURP3tWuSF1bZOqKTD9PZIrTZN65HY2eO+SUrAkF7ULiXgfMTcoK3nX
+NLIwfPqS2aWPf+gRH09YCAz7uqDkEfJzOkNCCgbZh9WsNVCmNwXFw3kAj4799im
5ujsjP3BR1MBQolG6nlKdhNE4UvE3l0CAwEAAaNTMFEwHQYDVR0OBBYEFBYEcrWZ
14D12I7TP0rAaDqQn4s6MB8GA1UdIwQYMBaAFBYEcrWZ14D12I7TP0rAaDqQn4s6
MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBAJonSlHPFarS/+o7
wfcYG/8Rjb7P5N+g9XAf3TLrNO+YnvrsFk02ilafuCPiBbtKDJ+aWsXbfO0u6hbL
R7f7QdV/p4YvuHPJ6k8SIsyDQ5JqoY5ch1/tGE/579Xt2OGZjdMyGGoNMfaKhmzG
ybSKamU3Nflc2X0KdF0MtIGT9+UNTJUj7BPb4gLF+pQzD/QMpr9Krd+e7uyXGGEg
JII9x71dYmLsCUdZmYxQZoht+FnAHSAKuTeE9Qha32pnfErOC//fRHjVzG6RIVnI
XUx3olcXM15frjwNrWoz5g59S6/sGrJS8vEmm+LFkrqCwq69u3m1o2oEm1b4ge9v
6MhpQSE=
-----END CERTIFICATE-----
)EOF";

    const char mosquitto_pub_key[] PROGMEM = R"KEY(
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvw+Xha3htXbVflUgnGmh
Q43M25sgIWkeeetvkl3bTptWuLwY0m4UtP10IaojDJEhxcTg1LsxzYf4xlUWp1BT
E7iz8dH/HrkfSKAfzBX30C7rqSAX6xX+Ca1qq5Q/IrQUOZYGHs97Sl9imO5nJz5K
B3g2f/byn8L2n/TIPrr6r/ac3qG8LLwbsCzDM5w18SNPqhpi5ksSKPFnl+pRBDQA
MxiQg6zulZFyyjChxg6YVWwoAeWELXXdzPaJoqokkLXd+BOCTAeql5RC7Jl1dQP9
jgoF3HsPk2Ah3qAg4rrak9GuAK2hS5cLNJADYegVqkVh11WQ3wHaUl5xnb3vVnL8
OwIDAQAB
-----END PUBLIC KEY-----
)KEY";

}
