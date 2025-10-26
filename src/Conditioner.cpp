#pragma once
#include<iostream>
#include <Conditioner.h>
#include"../include/ControllableDevice.h"
#include "string"
Conditioner::Conditioner():isOn(false),temperature(20) {
	std::cout<<"conditioner connected"<<std::endl;
}
void Conditioner :: turnOn() {
	isOn = true;
	std::cout << "conditioner is turned on" << std::endl;
}
void Conditioner::turnOff() {
	isOn = false;
	std::cout << "conditioner is turned off" << std::endl;
}
void Conditioner::setTemperature(int temp) {
	if (temp >= 13 && temp <= 31) {
		this->temperature = temp;
		std::cout << "temperature set to: " << temp;
	}
	else {
		std::cout << "invalid temperature value" << std::endl;
	}
}
int Conditioner::getTemperature() {
	return this->temperature;
}
std::string Conditioner::getStatus() {
	return isOn ? "conditioner is turned on" : "conditioner is turned off";
}