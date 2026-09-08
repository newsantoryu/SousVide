#ifndef DS18B20_TEMPERATURE_SENSOR_H
#define DS18B20_TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "../HAL/ITemperatureSensor.h"

class DS18B20TemperatureSensor : public ITemperatureSensor
{
public:
    explicit DS18B20TemperatureSensor(uint8_t pin);

    void begin() override;

    float readTemperature() override;

private:
    OneWire oneWire;
    DallasTemperature sensors;
};

#endif