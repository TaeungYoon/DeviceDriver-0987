#include "DeviceDriver.h"

class ReadFail : public std::exception
{};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)m_hardware->read(address);
    verifyRead(address, result);
    return result;
}

void DeviceDriver::verifyRead(long address, int value)
{
    for (int i = 0; i < MAX_VERIFY; i++) {
        int tempValue = (int)m_hardware->read(address);
        if (tempValue != value) {
            throw ReadFail();
        }
    }
}

void DeviceDriver::write(long address, int data)
{
    int readVal = m_hardware->read(address);
    m_hardware->write(address, (unsigned char)data);
}