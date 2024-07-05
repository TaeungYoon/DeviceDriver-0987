#include "app.h"
#include <iostream>

void Application::ReadAndPrint(long startAddr, long endAddr)
{
	for (long addr = startAddr; addr <= endAddr; addr++)
		std::cout 
		<< "READ ADDR: 0x" << std::hex << addr 
		<< ", VAL: " << deviceDriver->read(addr) 
		<< std::endl;
}

void Application::WriteAll(int value)
{
	for (int addr = 0x00; addr <= 0x04; addr++) {
		deviceDriver->write(addr, value);
	}
}
