#pragma once
#include <string>
#include "ControllableDevice.h" 

class LightBulb : public ControllableDevice {
private:
    bool isOn;
    std::string color ="white";
public:
    LightBulb();
    void turnOn() override;
    void turnOff() override;
    std::string getStatus() override;
    bool getIsOn() { return isOn; }
    void setColor(std::string color);
    std::string getColor();
};