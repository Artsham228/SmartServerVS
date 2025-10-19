#pragma once
#include "string"
#include "ControllableDevice.h"
class Conditioner :public ControllableDevice {
private: bool isOn;
public: 
	Conditioner();
	void turnOn() override;
	void turnOff() override;
	std::string getStatus()override;
};