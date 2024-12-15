#include <gtest/gtest.h>
#include "../src/XNORGateIC.cpp"

class XNORGateICTest : public ::testing::Test {
protected:
    XNORGateIC<bool> xnorGate;
};

TEST_F(XNORGateICTest, Constructor) {
    EXPECT_EQ(xnorGate.getTotalPins(), 14);
    EXPECT_EQ(xnorGate.getName(), "XNOR");
}

TEST_F(XNORGateICTest, Simulate) {
    xnorGate.connectVCC();
    xnorGate.connectGround();

    // Test pin pair (1, 2) -> (3)
    xnorGate.setPin(1, true);
    xnorGate.setPin(2, true);
    xnorGate.simulate();
    EXPECT_TRUE(xnorGate.getPin(3));

    xnorGate.setPin(1, true);
    xnorGate.setPin(2, false);
    xnorGate.simulate();
    EXPECT_FALSE(xnorGate.getPin(3));

    // Test pin pair (5, 6) -> (4)
    xnorGate.setPin(5, false);
    xnorGate.setPin(6, false);
    xnorGate.simulate();
    EXPECT_TRUE(xnorGate.getPin(4));

    // Test pin pair (13, 12) -> (11)
    xnorGate.setPin(13, true);
    xnorGate.setPin(12, false);
    xnorGate.simulate();
    EXPECT_FALSE(xnorGate.getPin(11));

    // Test pin pair (8, 9) -> (10)
    xnorGate.setPin(8, true);
    xnorGate.setPin(9, true);
    xnorGate.simulate();
    EXPECT_TRUE(xnorGate.getPin(10));
}

TEST_F(XNORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(xnorGate.simulate(), std::runtime_error);
}
