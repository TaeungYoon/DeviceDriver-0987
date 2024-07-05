#pragma once

#include "DeviceDriver.h"

class Application {
public:
	Application(DeviceDriver* driver) 
		: deviceDriver{ driver } 
	{}
	void ReadAndPrint(long startAddr, long endAddr);
	void WriteAll(int value);

private:
	DeviceDriver* deviceDriver;
};