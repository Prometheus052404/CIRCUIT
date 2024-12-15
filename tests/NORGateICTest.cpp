#include <gtest/gtest.h>
#include "../src/NORGateIC.cpp"

class NORGateICTest : public ::testing::Test {
protected:
    NORGateIC<bool> norGate;
};

TEST_F(NORGateICTest, Constructor) {
    EXPECT_EQ(norGate.getTotalPins(), 14);
    EXPECT_EQ(norGate.getName(), "NOR");
}

TEST_F(NORGateICTest, Simulate) {
    norGate.connectVCC();
    norGate.connectGround();

    // Test pin pair (2, 3) -> (1)
    norGate.setPin(2, false);
    norGate.setPin(3, false);
    norGate.simulate();
    EXPECT_TRUE(norGate.getPin(1));

    norGate.setPin(2, true);
    norGate.setPin(3, false);
    norGate.simulate();
    EXPECT_FALSE(norGate.getPin(1));

    // Test pin pair (5, 6) -> (4)
    norGate.setPin(5, false);
    norGate.setPin(6, false);
    norGate.simulate();
    EXPECT_TRUE(norGate.getPin(4));

    norGate.setPin(5, true);
    norGate.setPin(6, true);
    norGate.simulate();
    EXPECT_FALSE(norGate.getPin(4));

    // Test pin pair (11, 12) -> (13)
    norGate.setPin(11, true);
    norGate.setPin(12, true);
    norGate.simulate();
    EXPECT_FALSE(norGate.getPin(13));

    // Test pin pair (8, 9) -> (10)
    norGate.setPin(8, false);
    norGate.setPin(9, false);
    norGate.simulate();
    EXPECT_TRUE(norGate.getPin(10));
}

TEST_F(NORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(norGate.simulate(), std::runtime_error);
}
