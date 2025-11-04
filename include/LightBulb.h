#pragma once
#include <string>
#include "ControllableDevice.h" 

class LightBulb : public ControllableDevice {
private:
    bool isOn;
    std::string color ="white";
    int brightness=100; 
public:
    LightBulb();
    void turnOn() override;
    void turnOff() override;
    std::string getStatus() override;
    bool getIsOn() { return isOn; }
    bool setColor(std::string color);
    void setBrightness(int a);
    int getBrightness();
    std::string getColor();
};