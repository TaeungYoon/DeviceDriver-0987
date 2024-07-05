#include "DeviceDriver.h"

class ReadFail : public std::exception
{};

class WriteFail : public std::exception
{};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)m_hardware->read(address);
    verifyReadPass(address, result);
    return result;
}

void DeviceDriver::verifyReadPass(long address, int value)
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
    int result = m_hardware->read(address);
    verifyWritePass(result);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::verifyWritePass(int readVal)
{
    if (readVal != STATE_DELETE)
        throw WriteFail();
}
