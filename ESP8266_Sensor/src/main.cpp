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
  if (mqtt.CheckConnection())
  {

    mqtt.ReadIncoming();

    if ((millis() - last_sensor_read) / 1000 > mqtt_update_interval)
    {
      Weather_Sensor.readSensorData();

      mqtt.SendData(ESP_JSON_DATA, ComposeJsonESPstatus());
      last_sensor_read = millis();
    }
  }
  else
  {
    mqtt.reconnect();
  }
}

String ComposeJsonESPstatus()
{
  String ssid = wifi.getConnectedSSID();
  String ip = wifi.getNetworkiP();
  String rssi = wifi.getWiFiRSSI();
  String hostname = wifi.getHostname();
  String temp = Weather_Sensor.getTemp();
  String humidity = Weather_Sensor.getHumidity();
  String gas = Weather_Sensor.getGas();
  String presure = Weather_Sensor.getPresure();

  String Json_Data;

  StaticJsonDocument<200> doc;

  doc["ssid"] = ssid;
  doc["ip"] = ip;
  doc["rssi"] = rssi;
  doc["hostname"] = hostname;
  doc["sensor_temp"] = temp;
  doc["sensor_humidity"] = humidity;
  doc["sensor_gas"] = gas;
  doc["sensor_presure"] = presure;

  serializeJson(doc, Json_Data);

  if (debug_mode)
  {
    Serial.print("Composed Json : " + Json_Data);
  }

  return Json_Data;
}
