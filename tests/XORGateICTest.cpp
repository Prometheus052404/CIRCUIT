#include <gtest/gtest.h>
#include "../src/XORGateIC.cpp"

class XORGateICTest : public ::testing::Test {
protected:
    XORGateIC<bool> xorGate;
};

TEST_F(XORGateICTest, Constructor) {
    EXPECT_EQ(xorGate.getTotalPins(), 14);
    EXPECT_EQ(xorGate.getName(), "XOR");
}

TEST_F(XORGateICTest, Simulate) {
    xorGate.connectVCC();
    xorGate.connectGround();

    xorGate.setPin(1, true);
    xorGate.setPin(2, false);
    EXPECT_NO_THROW(xorGate.simulate());
    EXPECT_TRUE(xorGate.getPin(3));

    xorGate.setPin(1, true);
    xorGate.setPin(2, true);
    xorGate.simulate();
    EXPECT_FALSE(xorGate.getPin(3));
}

TEST_F(XORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(xorGate.simulate(), std::runtime_error);
}
