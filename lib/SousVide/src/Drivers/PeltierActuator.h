#pragma once

#include <Arduino.h>
#include "HAL/IPowerActuator.h"

class PeltierActuator : public IPowerActuator
{
private:
    uint8_t pwmPin;
    float currentPowerPercent;

    static constexpr uint32_t PWM_FREQUENCY = 5000;
    static constexpr uint8_t PWM_RESOLUTION = 8;

public:
    explicit PeltierActuator(uint8_t pin)
        : pwmPin(pin),
          currentPowerPercent(0.0f)
    {
    }

    void begin() override
    {
        ledcAttach(
            pwmPin,
            PWM_FREQUENCY,
            PWM_RESOLUTION
        );

        stop();
    }

    void setPowerPercent(float percent) override
    {
        percent = constrain(percent, 0.0f, 100.0f);

        const uint32_t maxDuty =
            (1 << PWM_RESOLUTION) - 1;

        const uint32_t duty =
            static_cast<uint32_t>(
                (percent / 100.0f) * maxDuty
            );

        ledcWrite(pwmPin, duty);

        currentPowerPercent = percent;
    }

    void stop() override
    {
        setPowerPercent(0.0f);
    }

    float getPowerPercent() const override
    {
        return currentPowerPercent;
    }
};