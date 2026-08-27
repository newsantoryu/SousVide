#include "DS18B20TemperatureSensor.h"

DS18B20TemperatureSensor::DS18B20TemperatureSensor(uint8_t pin)
    : oneWire(pin),
      sensors(&oneWire)
{
}

void DS18B20TemperatureSensor::begin()
{
    sensors.begin();
}

float DS18B20TemperatureSensor::readTemperature()
{
    sensors.requestTemperatures();

    return sensors.getTempCByIndex(0);
}