#pragma once
#include <string>
#include "ControllableDevice.h" 
class Door :public ControllableDevice {
private: bool isOn;
public:
	Door();
	void turnOn() override;
	void turnOff() override;
	std::string getStatus()override;
	bool getIsOn() { return isOn; }
};