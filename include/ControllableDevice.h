#pragma once 
#include <string>

class ControllableDevice {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() = 0;

    
    virtual ~ControllableDevice() = default;
};