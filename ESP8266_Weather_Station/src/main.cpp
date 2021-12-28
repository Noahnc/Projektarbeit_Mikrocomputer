#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <PubSubClient.h>
#include <Wire.h>
#include <iostream>
#include <string>
#include <config.h>
#include "RGB_LED_Handler.h"
#include <WiFi_Handler.h>
#include <MQTT_Client.h>
#include <Sensor_Handler.cpp>
#include <Arduino.h>

// sensor
int max_cycle = 1000;
int current_cycle = 0;

RGB_LED_Handler rgbLED = RGB_LED_Handler(led_blue, led_green, led_red);
WiFi_Handler wifi = WiFi_Handler(wifi_ssid, wifi_password);
MQTT_Client mqtt = MQTT_Client(mqtt_server, &rgbLED);
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

    current_cycle++;
    if (current_cycle == max_cycle)
    {
      Serial.println(current_cycle);
      Weather_Sensor.readSensorData();

      mqtt.SendData(temp_topic, Weather_Sensor.getTemp());
      mqtt.SendData(humidity_topic, Weather_Sensor.getHumidity());
      mqtt.SendData(gas_topic, Weather_Sensor.getGas());
      mqtt.SendData(preassure_topic, Weather_Sensor.getPreassure());
      current_cycle = 0;
    }
  }else
  {
    mqtt.reconnect();
  }
  
  delay(10);
}
