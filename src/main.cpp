#include <Arduino.h>

#include "Drivers/DS18B20TemperatureSensor.h"
#include "Drivers/PeltierActuator.h"

#include "Application/SousVideController.h"

#include "Config/HardwareConfig.h"

DS18B20TemperatureSensor ds18b20(DS18B20_PIN);

PeltierActuator peltier(PELTIER_PWM_PIN);

SousVideController sousVide(
    ds18b20,
    peltier
);

void setup()
{
    Serial.begin(115200);

    sousVide.begin();

    sousVide.setTargetTemperature(30.0f);

    Serial.println();
    Serial.println("================================");
    Serial.println("       SOPHIA SOUS VIDE");
    Serial.println("       SYSTEM CONTROLLER");
    Serial.println("================================");

    Serial.println("DS18B20 iniciado");
    Serial.println("Peltier Actuator iniciado");

    Serial.print("Temperatura alvo: ");
    Serial.print(sousVide.getTargetTemperature());
    Serial.println(" C");

    Serial.println("--------------------------------");

    // TESTE DA MAQUINA DE ESTADOS
    Serial.println("Chamando START...");

    sousVide.start();

    Serial.println("START chamado.");
}

void loop()
{
    sousVide.update();

    Serial.print("Temperatura: ");
    Serial.print(sousVide.getCurrentTemperature());
    Serial.print(" C");

    Serial.print(" | Alvo: ");
    Serial.print(sousVide.getTargetTemperature());
    Serial.print(" C");

    Serial.print(" | PWM: ");
    Serial.print(sousVide.getPowerPercent());
    Serial.print("%");

    Serial.print(" | Estado: ");

    switch (sousVide.getState())
    {
        case SystemState::IDLE:
            Serial.println("IDLE");
            break;

        case SystemState::HEATING:
            Serial.println("HEATING");
            break;

        case SystemState::TARGET_REACHED:
            Serial.println("TARGET_REACHED");
            break;

        case SystemState::FAULT:
            Serial.println("FAULT");
            break;
    }

    delay(1000);
}