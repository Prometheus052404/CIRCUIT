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

    // Test pin pair (1, 2) -> (3)
    orGate.setPin(1, true);
    orGate.setPin(2, false);
    orGate.simulate();
    EXPECT_TRUE(orGate.getPin(3));

    orGate.setPin(1, false);
    orGate.setPin(2, false);
    orGate.simulate();
    EXPECT_FALSE(orGate.getPin(3));

    // Test pin pair (4, 5) -> (6)
    orGate.setPin(4, true);
    orGate.setPin(5, true);
    orGate.simulate();
    EXPECT_TRUE(orGate.getPin(6));

    orGate.setPin(4, false);
    orGate.setPin(5, false);
    orGate.simulate();
    EXPECT_FALSE(orGate.getPin(6));

    // Test pin pair (9, 10) -> (8)
    orGate.setPin(9, false);
    orGate.setPin(10, true);
    orGate.simulate();
    EXPECT_TRUE(orGate.getPin(8));

    // Test pin pair (12, 13) -> (11)
    orGate.setPin(12, true);
    orGate.setPin(13, false);
    orGate.simulate();
    EXPECT_TRUE(orGate.getPin(11));
}

TEST_F(ORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(orGate.simulate(), std::runtime_error);
}
