#include <door.h>
#include <iostream>
#include "../include/ControllableDevice.h"
Door::Door() : isOpen(false),isLocked(true) {
	std::cout << "door connected" << std::endl;
}
void Door::Open() {
	isOpen = true;
	std::cout << "Door is open" << std::endl;
}
void Door::turnOn() {
	this->Open(); 
}
void Door::turnOff() {
	this->Close(); 
}
void Door::Close() {
	isOpen = false;
	std::cout << "Door is close" << std::endl;
}
void Door::setLock(bool d_stat) {
	 isLocked = d_stat;
	std::cout << "Door status set to:" << d_stat;
}
std::string Door::getStatus() {
	return isLocked ? "Door is locked" : "Door is unlocked";
}