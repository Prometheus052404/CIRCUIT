#include <gtest/gtest.h>

#include "../src/ANDGateIC.cpp"

// Test fixture for ANDGateIC
class ANDGateICTest : public ::testing::Test {
protected:
    ANDGateIC<bool> andGate;
};

// Test ANDGateIC Constructor
TEST_F(ANDGateICTest, Constructor) {
    EXPECT_EQ(andGate.getTotalPins(), 14);
    EXPECT_EQ(andGate.getName(), "AND");
}

// Test Simulate Method
TEST_F(ANDGateICTest, Simulate) {
    andGate.connectVCC();
    andGate.connectGround();

    // Set inputs for Gate 1
    andGate.setPin(1, true);
    andGate.setPin(2, true);

    // Simulate and check output
    EXPECT_NO_THROW(andGate.simulate());
    EXPECT_TRUE(andGate.getPin(3));

    // Set inputs for Gate 1
    andGate.setPin(1, true);
    andGate.setPin(2, false);

    // Simulate and check output
    andGate.simulate();
    EXPECT_FALSE(andGate.getPin(3));
}

// Test Simulate without Power
TEST_F(ANDGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(andGate.simulate(), std::runtime_error);
}