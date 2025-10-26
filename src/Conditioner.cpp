#pragma once
#include<iostream>
#include <Conditioner.h>
#include"../include/ControllableDevice.h"
#include "string"
Conditioner::Conditioner():isOn(false) {
	std::cout<<"conditioner created"<<std::endl;
}
void Conditioner :: turnOn() {
	isOn = true;
	std::cout << "conditioner is turned on" << std::endl;
}
void Conditioner::turnOff() {
	isOn = false;
	std::cout << "conditioner is turned off" << std::endl;
}