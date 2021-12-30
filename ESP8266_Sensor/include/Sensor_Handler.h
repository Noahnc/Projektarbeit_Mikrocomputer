#ifndef Sensor_Handler_h
#define Sensor_Handler_h

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
    String Presure;
    String Humidity;
    String Gas;
    String Altitude;

public:
    void init();
    bool readSensorData();
    String getTemp();
    String getPresure();
    String getHumidity();
    String getGas();
    String getAltitude();
};

#endif
