#ifndef I_TEMPERATURE_SENSOR_H
#define I_TEMPERATURE_SENSOR_H

class ITemperatureSensor
{
public:
    virtual ~ITemperatureSensor() {}

    virtual void begin() = 0;

    virtual float readTemperature() = 0;
};

#endif