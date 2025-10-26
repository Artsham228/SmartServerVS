#include <door.h>
#include <iostream>
#include "../include/ControllableDevice.h"
Door::Door() : isOn(false) {
	std::cout << "door connected" << std::endl;
}
void Door::turnOn() {
	isOn = true;
	std::cout << "Door is powered on" << std::endl;
}
void Door::turnOff() {
	isOn = false;
	std::cout << "Door is powered off" << std::endl;
}
std::string Door::getStatus() {
	return isOn ? "Door is open" : "Door is locked";
}