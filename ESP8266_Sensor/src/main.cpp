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
#include <chrono>

using namespace config_constants;

double last_sensor_read = 0;
double time_diference;


// Erstellen der Objekte
MQTT_Handler mqtt = MQTT_Handler(mosquito_server);
WiFi_Handler wifi = WiFi_Handler(wifi_ssid, wifi_wpa_psk);
Sensor_Handler Weather_Sensor = Sensor_Handler();

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

    time_diference = millis() - last_sensor_read;
    if (time_diference / 1000 > sensor_interval)
    {
      Weather_Sensor.readSensorData();

      mqtt.SendData(temp_topic, Weather_Sensor.getTemp());
      mqtt.SendData(humidity_topic, Weather_Sensor.getHumidity());
      mqtt.SendData(gas_topic, Weather_Sensor.getGas());
      mqtt.SendData(preassure_topic, Weather_Sensor.getPreassure());
      last_sensor_read = millis();
    }
  }
  else
  {
    mqtt.reconnect();
  }
}
