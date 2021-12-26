#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <PubSubClient.h>
#include <Wire.h>
#include <iostream>
#include <string>


// wifi
#define wifi_ssid "CCT Sitzungszimmer"
#define wifi_password "CCT-$itzun@Glatt18"

// sensor
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme;
int max_cycle = 1000;
int current_cycle = 0;

// mqtt
#define mqtt_server "raspberrypi-noah.local"
#define temp_topic "temperature"
#define humidity_topic "humidity"
#define preassure_topic "preasure"
#define gas_topic "gas"
#define rgb_topic "rgb"
#define rgb_switch_topic "switch"

WiFiClient espClient;
PubSubClient client(espClient);

// pins
int led_red = 15;
int led_green = 13;
int led_blue = 12;

// RGB Led
int red_value = 0;
int green_value = 0;
int blue_value = 0;
bool isOn = true;

// Setup and init
void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  initWlan();
  initSensor();
  initMqtt();
  initPins();
}

void initPins() {
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
}

void initMqtt() {
  Serial.print("Connecting to mqtt...");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void initWlan() {
  Serial.println();
  Serial.print("Connecting to wifi...");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  Serial.println("");
  Serial.println("Wifi Connected");
}

void initSensor() {
  Serial.println("BME680 async test");

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

// Loop
void loop() {
  // Mqtt
  if(!client.connected()) {
    Serial.println("MQTT not connected. Reconnecting...");
    reconnect();
  }

  client.loop();

  current_cycle++;
  if(current_cycle == max_cycle) {
    Serial.println(current_cycle);
    readSensorData();
    current_cycle = 0;
  }

  handleRgb();
  delay(10);
}

void handleRgb() {
  if(isOn) {
    analogWrite(led_red, red_value);
    analogWrite(led_green, green_value);
    analogWrite(led_blue, blue_value);
  } else {
    analogWrite(led_red, 0);
    analogWrite(led_green, 0);
    analogWrite(led_blue, 0);
  }
}

void readSensorData() {
  // Server
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println("Failed to begin reading :(");
    return;
  }

  Serial.print("Reading started at ");
  Serial.print(millis());

  Serial.print(" and will finish at ");
  Serial.println(endTime);

  delay(50);
  if (!bme.endReading()) {
    Serial.println("Failed to complete reading :(");
    return;
  }

  Serial.print("Reading completed at ");
  Serial.println(millis());

  // Temperature
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  String temp_string;
  temp_string += bme.temperature;  
  client.publish(temp_topic, (char*) temp_string.c_str());

  // Preassure
  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  String preassure_string;
  preassure_string += (bme.pressure / 100.0);  
  client.publish(preassure_topic, (char*) preassure_string.c_str());

  // Humidity
  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  String hum_string;
  hum_string += bme.humidity;  
  client.publish(humidity_topic, (char*) hum_string.c_str());

  // Gas
  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  String gas_string;
  gas_string += (bme.gas_resistance / 1000.0);  
  client.publish(gas_topic, (char*) gas_string.c_str());

  // Altitude
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}

// MqTT
void reconnect() {
  while(!client.connected()) {
    Serial.print("Attemping MQTT connection...");

    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);

    if(client.connect(clientId.c_str())) {
      Serial.print("Connecting to mqtt topics...");
      client.connect(temp_topic);
      client.connect(humidity_topic);
      client.connect(preassure_topic);
      client.connect(gas_topic);

      client.subscribe(rgb_topic);
      client.subscribe(rgb_switch_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.println();
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  
  String messageTemp;
  for(int i = 0; i < length; i++) {
    Serial.print((char) message[i]);
    messageTemp += (char) message[i];
  }

  Serial.println();
  if(String(topic) == rgb_topic) {
    Serial.println(messageTemp);
    Serial.print("Changing led rgb value");

    int number = (int) strtol( &messageTemp[0], NULL, 16);
    red_value = number >> 16;
    green_value = number >> 8 & 0xFF;
    blue_value = number & 0xFF;
  } else if(String(topic) == rgb_switch_topic) {
    Serial.println(messageTemp);
    Serial.print("Changing led on off state");

    if(messageTemp == "true") {
      isOn = true;
    } else {
      isOn = false;
    }
  }
}