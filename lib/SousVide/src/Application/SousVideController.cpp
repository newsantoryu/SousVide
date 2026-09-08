#include "SousVideController.h"

#include <Arduino.h>

SousVideController::SousVideController(
    ITemperatureSensor& temperatureSensor,
    IPowerActuator& powerActuator
)
    : temperatureSensor(temperatureSensor),
      powerActuator(powerActuator),
      targetTemperature(30.0f),
      currentTemperature(0.0f),
      state(SystemState::IDLE)
{
}

void SousVideController::begin()
{
    temperatureSensor.begin();
    powerActuator.begin();

    powerActuator.stop();

    state = SystemState::IDLE;
}

void SousVideController::start()
{
    if (state == SystemState::FAULT)
    {
        return;
    }

    state = SystemState::HEATING;
}

void SousVideController::stop()
{
    powerActuator.stop();

    state = SystemState::IDLE;
}

void SousVideController::reset()
{
    powerActuator.stop();

    if (state == SystemState::FAULT)
    {
        state = SystemState::IDLE;
    }
}

void SousVideController::update()
{
    currentTemperature = temperatureSensor.readTemperature();

    // Proteção contra sensor desconectado ou leitura inválida
    if (!isTemperatureValid(currentTemperature))
    {
        powerActuator.stop();

        state = SystemState::FAULT;

        return;
    }

    // Sistema parado
    if (state == SystemState::IDLE)
    {
        powerActuator.stop();

        return;
    }

    // Falha mantém o atuador desligado
    if (state == SystemState::FAULT)
    {
        powerActuator.stop();

        return;
    }

    // Sistema em aquecimento
    if (state == SystemState::HEATING)
    {
        if (currentTemperature >= targetTemperature)
        {
            powerActuator.stop();

            state = SystemState::TARGET_REACHED;

            return;
        }

        powerActuator.setPowerPercent(HEATING_POWER);

        return;
    }

    // Temperatura alvo atingida
    if (state == SystemState::TARGET_REACHED)
    {
        powerActuator.stop();

        if (currentTemperature <= (targetTemperature - HYSTERESIS))
        {
            state = SystemState::HEATING;

            powerActuator.setPowerPercent(HEATING_POWER);
        }

        return;
    }
}

bool SousVideController::isTemperatureValid(float temperature) const
{
    if (isnan(temperature))
    {
        return false;
    }

    if (temperature < -55.0f || temperature > 125.0f)
    {
        return false;
    }

    return true;
}

float SousVideController::getCurrentTemperature() const
{
    return currentTemperature;
}

void SousVideController::setTargetTemperature(float temperature)
{
    targetTemperature = temperature;
}

float SousVideController::getTargetTemperature() const
{
    return targetTemperature;
}

float SousVideController::getPowerPercent() const
{
    return powerActuator.getPowerPercent();
}

bool SousVideController::isRunning() const
{
    return state != SystemState::IDLE &&
           state != SystemState::FAULT;
}

SystemState SousVideController::getState() const
{
    return state;
}