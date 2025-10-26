#include <LightBulb.h>
#include <iostream>
#include "../include/ControllableDevice.h"
LightBulb::LightBulb():	 isOn(false) {
	std::cout << "LightBulb connected" << std::endl;
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
	return isOn  ? "bulb turned on, color:"+color : "bulb turned off" ;
}
void LightBulb::setColor(std::string newColor) {
	this->color = newColor;
	std::cout << "Bulb color set to:" << newColor;
}
std::string LightBulb::getColor() {
	return this->color;
}