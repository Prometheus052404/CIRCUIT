#include <gtest/gtest.h>
#include "../src/ANDGateIC.cpp"

class ANDGateICTest : public ::testing::Test {
protected:
    ANDGateIC<bool> andGate;
};

TEST_F(ANDGateICTest, Constructor) {
    EXPECT_EQ(andGate.getTotalPins(), 14);
    EXPECT_EQ(andGate.getName(), "AND");
}

TEST_F(ANDGateICTest, Simulate) {
    andGate.connectVCC();
    andGate.connectGround();

    // Test pin pair (1, 2) -> (3)
    andGate.setPin(1, true);
    andGate.setPin(2, true);
    EXPECT_NO_THROW(andGate.simulate());
    EXPECT_TRUE(andGate.getPin(3));

    andGate.setPin(1, true);
    andGate.setPin(2, false);
    andGate.simulate();
    EXPECT_FALSE(andGate.getPin(3));

    // Test pin pair (4, 5) -> (6)
    andGate.setPin(4, true);
    andGate.setPin(5, true);
    andGate.simulate();
    EXPECT_TRUE(andGate.getPin(6));

    andGate.setPin(4, false);
    andGate.setPin(5, true);
    andGate.simulate();
    EXPECT_FALSE(andGate.getPin(6));

    // Test pin pair (9, 10) -> (8)
    andGate.setPin(9, true);
    andGate.setPin(10, true);
    andGate.simulate();
    EXPECT_TRUE(andGate.getPin(8));

    andGate.setPin(9, false);
    andGate.setPin(10, true);
    andGate.simulate();
    EXPECT_FALSE(andGate.getPin(8));

    // Test pin pair (12, 13) -> (11)
    andGate.setPin(12, true);
    andGate.setPin(13, true);
    andGate.simulate();
    EXPECT_TRUE(andGate.getPin(11));

    andGate.setPin(12, true);
    andGate.setPin(13, false);
    andGate.simulate();
    EXPECT_FALSE(andGate.getPin(11));
}

TEST_F(ANDGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(andGate.simulate(), std::runtime_error);
}
