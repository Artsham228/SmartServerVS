#pragma once
#include <string>
#include "ControllableDevice.h" 
class Door :public ControllableDevice {
private: bool isLocked;
	   bool isOpen;
public:
	Door();
	void turnOn() override;
	void turnOff() override;
	void Open();
	void Close();
	void setLock(bool);
	std::string getStatus()override;
	bool getIsLocked() { return isLocked; }
	bool getIsOpen() { return isOpen; };
};