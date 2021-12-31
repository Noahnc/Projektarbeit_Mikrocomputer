/* 
########################################################################
#                          Sensor Handler
########################################################################
#                           Description
#         Handelt das Auslesen eines BME680 Climate Sensors
*/

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <Wire.h>
#include <iostream>
#include "Sensor_Handler.h"
#include "00config.h"

using namespace config_constants;

void Sensor_Handler::init()
{
    if (debug_mode)
    {
        Serial.println("BME680 async test");
    }

    if (!bme.begin())
    {
        if (debug_mode)
        {
            Serial.println("Could not find a valid BME680 sensor, check wiring!");
        }
        while (1)
            ;
    }

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
}

bool Sensor_Handler::readSensorData()
{
    // Server
    unsigned long endTime = bme.beginReading();
    if (endTime == 0)
    {
        if (debug_mode)
        {
            Serial.println("Failed to begin reading :(");
        }
        return false;
    }

    if (debug_mode)
    {
        Serial.print("Sensor Reading started at ");
        Serial.print(millis());

        Serial.print(" and will finish at ");
        Serial.println(endTime);
    }

    delay(50);
    if (!bme.endReading())
    {
        if (debug_mode)
        {
            Serial.println("Failed to complete reading :(");
        }

        return false;
    }

    if (debug_mode)
    {
        Serial.print("Reading completed at ");
        Serial.println(millis());
    }

    // Temperature
    if (debug_mode)
    {
        Serial.print("Temperature = ");
        Serial.print(bme.temperature);
        Serial.println(" *C");
    }
    Temparature = "";
    Temparature += bme.temperature;

    // Preassure
    if (debug_mode)
    {
        Serial.print("Pressure = ");
        Serial.print(bme.pressure / 100.0);
        Serial.println(" hPa");
    }
    Presure = "";
    Presure += (bme.pressure / 100.0);

    // Humidity
    if (debug_mode)
    {
        Serial.print("Humidity = ");
        Serial.print(bme.humidity);
        Serial.println(" %");
    }
    Humidity = "";
    Humidity += bme.humidity;

    // Gas
    if (debug_mode)
    {
        Serial.print("Gas = ");
        Serial.print(bme.gas_resistance / 1000.0);
        Serial.println(" KOhms");
    }
    Gas = "";
    Gas += (bme.gas_resistance / 1000.0);

    // Altitude
    if (debug_mode)
    {
        Serial.print("Approx. Altitude = ");
        Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
        Serial.println(" m");
    }
    Altitude = "";
    Altitude += bme.readAltitude(SEALEVELPRESSURE_HPA);

    Serial.println();
    delay(2000);
    return true;
}

float Sensor_Handler::getTemp()
{
    return Temparature.toFloat();
}

float Sensor_Handler::getPresure()
{
    return Presure.toFloat();
}

float Sensor_Handler::getHumidity()
{
    return Humidity.toFloat();
}
float Sensor_Handler::getGas()
{
    return Gas.toFloat();
}

float Sensor_Handler::getAltitude()
{
    return Altitude.toFloat();
}
