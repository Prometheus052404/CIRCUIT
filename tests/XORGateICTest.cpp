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

    // Test pin pair (1, 2) -> (3)
    xorGate.setPin(1, true);
    xorGate.setPin(2, false);
    xorGate.simulate();
    EXPECT_TRUE(xorGate.getPin(3));

    xorGate.setPin(1, true);
    xorGate.setPin(2, true);
    xorGate.simulate();
    EXPECT_FALSE(xorGate.getPin(3));

    // Test pin pair (4, 5) -> (6)
    xorGate.setPin(4, false);
    xorGate.setPin(5, false);
    xorGate.simulate();
    EXPECT_FALSE(xorGate.getPin(6));

    xorGate.setPin(4, true);
    xorGate.setPin(5, true);
    xorGate.simulate();
    EXPECT_FALSE(xorGate.getPin(6));

    // Test pin pair (9, 10) -> (8)
    xorGate.setPin(9, false);
    xorGate.setPin(10, true);
    xorGate.simulate();
    EXPECT_TRUE(xorGate.getPin(8));

    // Test pin pair (12, 13) -> (11)
    xorGate.setPin(12, false);
    xorGate.setPin(13, true);
    xorGate.simulate();
    EXPECT_TRUE(xorGate.getPin(11));
}

TEST_F(XORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(xorGate.simulate(), std::runtime_error);
}
