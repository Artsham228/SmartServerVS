#pragma once
#include "string"
#include "ControllableDevice.h"
class Conditioner :public ControllableDevice {
private: bool isOn;
	   int temperature;
public: 
	Conditioner();
	void turnOn() override;
	void turnOff() override;
	std::string getStatus()override;
	bool getIsOn() { return isOn; }
	int getTemperature();
	void setTemperature(int temp);
};