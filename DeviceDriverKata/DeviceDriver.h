#pragma once
#include "FlashMemoryDevice.h"
#include <exception>
#include <string>

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

private:
    void verifyReadPass(long address, int t);
    void verifyWritePass(int readVal);

    FlashMemoryDevice* m_hardware;
    const int MAX_VERIFY = 4;
    const int STATE_DELETE = 0XFF;
};
