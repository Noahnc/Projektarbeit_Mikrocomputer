/*
########################################################################
# Mikrocomputertechnik Projektarbeit by Noah Canadea and Milan Bursac
########################################################################
#                           Description
#       ESP8266 Code für BME Temparatursensor und RGB LED Steuerung
#
#                    Version 1.0 | 10.01.2021 */

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <Wire.h>
#include <iostream>
#include <string>
#include "00config.h"
#include "RGB_LED_Handler.h"
#include "WiFi_Handler.h"
#include "MQTT_Handler.h"
#include "Sensor_Handler.h"
#include <Arduino.h>
#include "01mqtt_topics.h"
#include <ArduinoJson.h>
#include <chrono>

using namespace config_constants;

double last_sensor_read = 0;
double time_diference;

// Erstellen der Objekte
MQTT_Handler mqtt = MQTT_Handler(mosquito_server);
WiFi_Handler wifi = WiFi_Handler(wifi_ssid, wifi_wpa_psk);
Sensor_Handler Weather_Sensor = Sensor_Handler();

// Function declaration
String ComposeJsonESPstatus();
void HandleWiFiDisconnect();

// Setup and init
void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  wifi.init();
  Weather_Sensor.init();
  mqtt.init();
}

// Loop
void loop()
{
  HandleWiFiDisconnect();
  if (mqtt.CheckConnection())
  {
    // Update der
    mqtt.ReadIncoming();

    // Update des Sensors und senden der Daten wenn Update Intervall überschritten
    if ((millis() - last_sensor_read) / 1000 > mqtt_update_interval)
    {
      last_sensor_read = millis();
      Weather_Sensor.readSensorData();
      mqtt.SendData(ESP_JSON_DATA, ComposeJsonESPstatus());
    }
  }
  else
  {
    mqtt.reconnect();
  }
}

String ComposeJsonESPstatus()
{
  // Sammeln der Daten
  String ssid = wifi.getConnectedSSID();
  String ip = wifi.getNetworkiP();
  String rssi = wifi.getWiFiRSSI();
  String hostname = wifi.getHostname();
  float free_heap = ESP.getFreeHeap() / 1000;
  int heap_fragmentation = ESP.getHeapFragmentation();
  float temp = Weather_Sensor.getTemp();
  float humidity = Weather_Sensor.getHumidity();
  float gas = Weather_Sensor.getGas();
  float presure = Weather_Sensor.getPresure();

  String Json_Data;

  StaticJsonDocument<200> doc;

  // Zusammentragen der Daten zu einem Json String
  doc["ssid"] = ssid;
  doc["ip"] = ip;
  doc["rssi"] = rssi;
  doc["hostname"] = hostname;
  doc["sensor_temp"] = temp;
  doc["sensor_humidity"] = humidity;
  doc["sensor_gas"] = gas;
  doc["sensor_presure"] = presure;
  doc["esp_free_heap"] = free_heap;
  doc["esp_heap_fragmentation"] = heap_fragmentation;
  serializeJson(doc, Json_Data);

  if (debug_mode)
  {
    Serial.print("Composed Json : " + Json_Data);
  }

  return Json_Data;
}

void HandleWiFiDisconnect()
{
  if (wifi.CheckWiFiConnected() == false)
  {
    RGB_LED_Handler warn_led = RGB_LED_Handler(led_blue, led_green, led_red);
    warn_led.SetLedColor("ff0011");

    while (wifi.CheckWiFiConnected() == false)
    {
      warn_led.TurnOnLED();
      delay(100);
      warn_led.TurnOffLed();
      delay(100);
      warn_led.TurnOnLED();
      delay(100);
      warn_led.TurnOffLed();
      delay(100);
      warn_led.TurnOnLED();
      delay(100);
      warn_led.TurnOffLed();
      delay(3000);
    }
  }
}
