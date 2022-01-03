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
#include <NTPClient.h>
#include <WiFiUdp.h>

using namespace config_constants;

double last_sensor_read = 0;
double time_diference;
WiFiUDP ntpUDP;

// Erstellen der Objekte
MQTT_Handler mqtt = MQTT_Handler(mosquitto_server, mosquitto_user, mosquitto_pw, ESP_Hostname);
WiFi_Handler wifi = WiFi_Handler(wifi_ssid, wifi_wpa_psk, ESP_Hostname);
Sensor_Handler Weather_Sensor = Sensor_Handler();
NTPClient timeClient(ntpUDP, NTP_Server.c_str(), 3600);
RGB_LED_Handler led = RGB_LED_Handler(led_blue, led_green, led_red);

// Function declaration
String ComposeJsonESPstatus();
void HandleWiFiDisconnect();
void CheckMemoryFragmentation();
void UpdateTime();
void HandleMQTTDisconnect();
void StartupFinished();

// Setup and init
void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  wifi.init();
  timeClient.begin();
  UpdateTime();
  Weather_Sensor.init();
  mqtt.init();
  HandleMQTTDisconnect();
  StartupFinished();
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
      CheckMemoryFragmentation();
      UpdateTime();
    }
  }
  else
  {
    HandleMQTTDisconnect();
  }
}

String ComposeJsonESPstatus()
{
  String Json_Data;
  StaticJsonDocument<250> doc;

  // Zusammentragen der Daten zu einem Json String
  doc["ssid"] = wifi.getConnectedSSID();
  doc["ip"] = wifi.getNetworkiP();
  doc["rssi"] = wifi.getWiFiRSSI();
  doc["hostname"] = wifi.getHostname();
  doc["sensor_temp"] = Weather_Sensor.getTemp();
  doc["sensor_humidity"] = Weather_Sensor.getHumidity();
  doc["sensor_gas"] = Weather_Sensor.getGas();
  doc["sensor_presure"] = Weather_Sensor.getPresure();
  doc["esp_free_heap"] = ESP.getFreeHeap() / 1000;
  doc["esp_heap_fragmentation"] = ESP.getHeapFragmentation();
  serializeJson(doc, Json_Data);

  if (debug_mode)
  {
    Serial.println("Composed Json : " + Json_Data);
  }
  return Json_Data;
}

void HandleWiFiDisconnect()
{
  if (wifi.CheckWiFiConnected() == false)
  {
    led.SetLedColor("ff0011");
    int counter = 1;

    while (wifi.CheckWiFiConnected() == false)
    {
      while (counter < 7)
      {
        led.TurnOnLED();
        delay(100);
        led.TurnOffLed();
        delay(100);
        counter++;
      }
      delay(5000);
      counter = 1;
    }
  }
}

void HandleMQTTDisconnect()
{
  if (mqtt.CheckConnection() == false)
  {
    led.SetLedColor("FFB52E");
    int counter = 1;

    while (mqtt.CheckConnection() == false)
    {
      while (counter < 7)
      {
        led.TurnOnLED();
        delay(100);
        led.TurnOffLed();
        delay(100);
        counter++;
      }
      mqtt.reconnect();
      counter = 1;
    }
  }
}

void CheckMemoryFragmentation()
{
  if (ESP.getHeapFragmentation() > 85)
  {
    Serial.println("Heap fragmentation is to high, restart ESP board");
    ESP.restart();
  }
}

void UpdateTime()
{
  timeClient.update();
  if (debug_mode)
  {
    Serial.println("Aktuelle Zeit: " + timeClient.getFormattedTime());
  }
}

void StartupFinished()
{
  led.SetLedColor("00FF00");
  int counter = 1;
  while (counter < 7)
  {
    led.TurnOnLED();
    delay(100);
    led.TurnOffLed();
    delay(100);
    counter++;
  }

  led.TurnOnLED();
  delay(2000);
  led.TurnOffLed();
}
