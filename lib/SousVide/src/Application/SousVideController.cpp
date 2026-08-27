#include "SousVideController.h"

SousVideController::SousVideController(ITemperatureSensor& temperatureSensor) : temperatureSensor(temperatureSensor), targetTemperature(0.0) 
{ 

} 

void SousVideController::begin()
{ 
    temperatureSensor.begin(); 
} 

float SousVideController::readTemperature() 
{
    return temperatureSensor.readTemperature(); 
}
void SousVideController::setTargetTemperature(float temperature)
{
    targetTemperature = temperature;
}

float SousVideController::getTargetTemperature()
{
    return targetTemperature;
}

bool SousVideController::shouldHeat()
{
    float currentTemperature = readTemperature();

    return currentTemperature < targetTemperature;
}