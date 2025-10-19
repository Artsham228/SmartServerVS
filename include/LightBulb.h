#pragma once
#include <string>
#include "ControllableDevice.h" 

class LightBulb : public ControllableDevice {
private:
    bool isOn;

public:
    LightBulb();

    void turnOn() override;
    void turnOff() override;
    std::string getStatus() override;
};