#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriverKata/DeviceDriver.cpp"
#include "../DeviceDriverKata/FlashMemoryDevice.h"
#include <exception>

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTestFixture : public testing::Test
{
public:
	NiceMock<FlashMemoryDeviceMock> flashMock;
	DeviceDriver deviceDriver { &flashMock };
	long TEST_ADDRESS = 0x1234;
	int TEST_VALUE = 10;
	int READ_PASS_CNT = 5;
	int READ_PASS_VAL = 100;
	int READ_FAIL_VAL = 200;
	int WRITE_PASS_VAL = 0xFF;
	int WRITE_FAIL_VAL = 0xAA;
};

TEST_F(DeviceDriverTestFixture, ReadSuccessCase) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read(TEST_ADDRESS))
		.Times(READ_PASS_CNT)
		.WillRepeatedly(Return(READ_PASS_VAL));

	//assert
	int expected = READ_PASS_VAL;
	int actual = deviceDriver.read(TEST_ADDRESS);
	EXPECT_EQ(expected, actual);
}

TEST_F(DeviceDriverTestFixture, ReadFailCase) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read(TEST_ADDRESS))
		.Times(READ_PASS_CNT)
		.WillOnce(Return(READ_PASS_VAL))
		.WillOnce(Return(READ_PASS_VAL))
		.WillOnce(Return(READ_PASS_VAL))
		.WillOnce(Return(READ_PASS_VAL))
		.WillOnce(Return(READ_FAIL_VAL));

	//assert
	EXPECT_THROW(
		{ deviceDriver.read(TEST_ADDRESS); },
		ReadFail
	);
}

TEST_F(DeviceDriverTestFixture, WriteSuccessCase) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read(TEST_ADDRESS))
		.Times(1)
		.WillRepeatedly(Return(WRITE_PASS_VAL));

	//assert
	deviceDriver.write(TEST_ADDRESS, TEST_VALUE);
}

TEST_F(DeviceDriverTestFixture, WriteFailCase) {
	//arrange

	//act
	EXPECT_CALL(flashMock, read(TEST_ADDRESS))
		.Times(1)
		.WillRepeatedly(Return(WRITE_FAIL_VAL));

	//assert
	EXPECT_THROW(
		{ deviceDriver.write(TEST_ADDRESS, TEST_VALUE); },
		std::exception
	);
}