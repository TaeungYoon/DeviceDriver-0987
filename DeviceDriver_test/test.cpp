#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriverKata/DeviceDriver.cpp"
#include "../DeviceDriverKata/FlashMemoryDevice.h"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTestFixture : public testing::Test
{
public:
	FlashMemoryDeviceMock flashMock;
	DeviceDriver deviceDriver { &flashMock };
	long READ_ADDRESS = 0x1234;
	long READ_PASS_CNT = 5;
	long READ_PASS_VAL = 100;
	long READ_FAIL_VAL = 200;
};

TEST_F(DeviceDriverTestFixture, ReadFiveTimes) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read)
		.Times(READ_PASS_CNT);

	//assert
	deviceDriver.read(READ_ADDRESS);
}

TEST_F(DeviceDriverTestFixture, ReadFiveTimesAndReturnSuccess) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read)
		.Times(READ_PASS_CNT)
		.WillRepeatedly(Return(READ_PASS_VAL));

	//assert
	deviceDriver.read(READ_ADDRESS);
}

