#include <LightBulb.h>
#include <iostream>
#include <set>
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
bool LightBulb::setColor(std::string newColor) {

    const std::set<std::string> validColors = {
        "white", "red", "green", "blue", "yellow", "purple", "orange"
    };

    if (validColors.count(newColor)) {
        this->color = newColor;
        std::cout << "Bulb color set to " << newColor << std::endl;
        return true;
    }
    else {
        std::cout << "Invalid color received: " << newColor << std::endl;
        return false;
    }
}
std::string LightBulb::getColor() {
	return this->color;
}
void LightBulb::setBrightness(int bright) {
	this->brightness = bright;
	std::cout << "Bulb brighness set to:" << brightness<<"%";
}
int LightBulb::getBrightness() {
	return this->brightness;
}