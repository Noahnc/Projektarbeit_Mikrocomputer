#pragma once
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <Wire.h>
#include <iostream>

class Sensor_Handler
{
private:
#define SEALEVELPRESSURE_HPA (1013.25)
    Adafruit_BME680 bme;
    String Temparature;
    String Preassure;
    String Humidity;
    String Gas;
    String Altitude;

public:
    void init();
    bool readSensorData();
    String getTemp();
    String getPreassure();
    String getHumidity();
    String getGas();
    String getAltitude();
};
