#include <Arduino.h>

#include "Drivers/DS18B20TemperatureSensor.h"
#include "Application/SousVideController.h"
#include "Config/HardwareConfig.h"

DS18B20TemperatureSensor ds18b20(DS18B20_PIN);

SousVideController sousVide(ds18b20);

void setup()
{
    Serial.begin(115200);

    sousVide.begin();

    sousVide.setTargetTemperature(55);

    Serial.println("Sous Vide");
    Serial.println("DS18b20 iniciado");

    Serial.print("Temperatura desejada: ");
    Serial.print(sousVide.getTargetTemperature());
    Serial.println(" C");
}

void loop()
{
    float temperature = sousVide.readTemperature();

    Serial.print("Temperatura atual: ");
    Serial.print(temperature);
    Serial.println(" C");

    if (sousVide.shouldHeat())
    {
        Serial.println("Estado: AQUECER");
    }
    else
    {
        Serial.println("Estado: TEMPERATURA OK");
    }

    delay(1000);
}