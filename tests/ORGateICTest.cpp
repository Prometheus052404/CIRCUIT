#include <gtest/gtest.h>
#include "../src/ORGateIC.cpp"

class ORGateICTest : public ::testing::Test {
protected:
    ORGateIC<bool> orGate;
};

TEST_F(ORGateICTest, Constructor) {
    EXPECT_EQ(orGate.getTotalPins(), 14);
    EXPECT_EQ(orGate.getName(), "OR");
}

TEST_F(ORGateICTest, Simulate) {
    orGate.connectVCC();
    orGate.connectGround();

    orGate.setPin(1, true);
    orGate.setPin(2, false);

    EXPECT_NO_THROW(orGate.simulate());
    EXPECT_TRUE(orGate.getPin(3));

    orGate.setPin(1, false);
    orGate.setPin(2, false);
    orGate.simulate();
    EXPECT_FALSE(orGate.getPin(3));
}

TEST_F(ORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(orGate.simulate(), std::runtime_error);
}
