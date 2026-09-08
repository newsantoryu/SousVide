#pragma once

class IPowerActuator
{
public:
    virtual ~IPowerActuator() = default;

    virtual void begin() = 0;

    virtual void setPowerPercent(float percent) = 0;

    virtual void stop() = 0;

    virtual float getPowerPercent() const = 0;
};