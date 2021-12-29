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
        Serial.println("BME680 async test");

        if (!bme.begin())
        {
            Serial.println("Could not find a valid BME680 sensor, check wiring!");
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
            Serial.println("Failed to begin reading :(");
            return false;
        }

        Serial.print("Reading started at ");
        Serial.print(millis());

        Serial.print(" and will finish at ");
        Serial.println(endTime);

        delay(50);
        if (!bme.endReading())
        {
            Serial.println("Failed to complete reading :(");
            return false;
        }

        Serial.print("Reading completed at ");
        Serial.println(millis());

        // Temperature
        Serial.print("Temperature = ");
        Serial.print(bme.temperature);
        Serial.println(" *C");
        Temparature = "";
        Temparature += bme.temperature;

        // Preassure
        Serial.print("Pressure = ");
        Serial.print(bme.pressure / 100.0);
        Serial.println(" hPa");
        Preassure = "";
        Preassure += (bme.pressure / 100.0);

        // Humidity
        Serial.print("Humidity = ");
        Serial.print(bme.humidity);
        Serial.println(" %");
        Humidity = "";
        Humidity += bme.humidity;

        // Gas
        Serial.print("Gas = ");
        Serial.print(bme.gas_resistance / 1000.0);
        Serial.println(" KOhms");
        Gas = "";
        Gas += (bme.gas_resistance / 1000.0);

        // Altitude
        Serial.print("Approx. Altitude = ");
        Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
        Serial.println(" m");
        Altitude = "";
        Altitude += bme.readAltitude(SEALEVELPRESSURE_HPA);

        Serial.println();
        delay(2000);
        return true;
    }

    String Sensor_Handler::getTemp()
    {
        return Temparature;
    }

    String Sensor_Handler::getPreassure()
    {
        return Preassure;
    }

    String Sensor_Handler::getHumidity()
    {
        return Humidity;
    }
    String Sensor_Handler::getGas()
    {
        return Gas;
    }

    String Sensor_Handler::getAltitude()
    {
        return Altitude;
    }

