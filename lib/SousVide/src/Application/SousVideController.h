#ifndef SOUS_VIDE_CONTROLLER_H 
#define SOUS_VIDE_CONTROLLER_H

#include "../HAL/ITemperatureSensor.h" 

class SousVideController
{ 
public: 
    SousVideController(ITemperatureSensor& temperatureSensor);

    void begin();

    float readTemperature();

    void setTargetTemperature(float temperature);
    
    float getTargetTemperature();

    bool shouldHeat();

private:
    ITemperatureSensor& temperatureSensor;
    float targetTemperature;
 }; 
 
 #endif