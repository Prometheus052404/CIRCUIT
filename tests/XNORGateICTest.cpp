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

    xnorGate.setPin(1, true);
    xnorGate.setPin(2, false);
    EXPECT_NO_THROW(xnorGate.simulate());
    EXPECT_FALSE(xnorGate.getPin(3));

    xnorGate.setPin(1, true);
    xnorGate.setPin(2, true);
    xnorGate.simulate();
    EXPECT_TRUE(xnorGate.getPin(3));
}

TEST_F(XNORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(xnorGate.simulate(), std::runtime_error);
}
