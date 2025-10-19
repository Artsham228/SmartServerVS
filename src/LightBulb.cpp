#include <LightBulb.h>
#include <iostream>
#include "../include/ControllableDevice.h"
LightBulb::LightBulb():	 isOn(false) {
	std::cout << "create bulb(off)" << std::endl;
	}
void LightBulb::turnOn() {
	isOn = true;
	std::cout << "bulb turned on" << std::endl;
}
void LightBulb::turnOff() {
	isOn = false;
	std::cout<<"bulb turned off"<<std::endl;
}
std::string LightBulb::getStatus() {
	return isOn  ? "bulb turned on" : "bulb turned off" ;
}