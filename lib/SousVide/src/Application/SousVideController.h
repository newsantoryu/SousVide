#ifndef SOUS_VIDE_CONTROLLER_H
#define SOUS_VIDE_CONTROLLER_H

#include "../HAL/ITemperatureSensor.h"
#include "../HAL/IPowerActuator.h"

#include "SystemState.h"

class SousVideController
{
public:
    SousVideController(
        ITemperatureSensor& temperatureSensor,
        IPowerActuator& powerActuator
    );

    void begin();

    void update();

    void start();

    void stop();

    void reset();

    float getCurrentTemperature() const;

    void setTargetTemperature(float temperature);

    float getTargetTemperature() const;

    float getPowerPercent() const;

    bool isRunning() const;

    SystemState getState() const;

private:
    ITemperatureSensor& temperatureSensor;
    IPowerActuator& powerActuator;

    float targetTemperature;
    float currentTemperature;

    SystemState state;

    static constexpr float HYSTERESIS = 0.5f;
    static constexpr float HEATING_POWER = 20.0f;

    bool isTemperatureValid(float temperature) const;
};

#endif