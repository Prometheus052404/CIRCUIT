#include <gtest/gtest.h>
#include "../src/NOTGateIC.cpp"

class NOTGateICTest : public ::testing::Test {
protected:
    NOTGateIC<bool> notGate;
};

TEST_F(NOTGateICTest, Constructor) {
    EXPECT_EQ(notGate.getTotalPins(), 14);
    EXPECT_EQ(notGate.getName(), "NOT");
}

TEST_F(NOTGateICTest, Simulate) {
    notGate.connectVCC();
    notGate.connectGround();

    // Test pin (1) -> (2)
    notGate.setPin(1, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(2));

    notGate.setPin(1, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(2));

    // Test pin (3) -> (4)
    notGate.setPin(3, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(4));

    notGate.setPin(3, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(4));

    // Test pin (5) -> (6)
    notGate.setPin(5, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(6));

    notGate.setPin(5, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(6));

    // Test pin (13) -> (12)
    notGate.setPin(13, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(12));

    notGate.setPin(13, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(12));

    // Test pin (11) -> (10)
    notGate.setPin(11, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(10));

    notGate.setPin(11, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(10));

    // Test pin (9) -> (8)
    notGate.setPin(9, true);
    notGate.simulate();
    EXPECT_FALSE(notGate.getPin(8));

    notGate.setPin(9, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(8));
}

TEST_F(NOTGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(notGate.simulate(), std::runtime_error);
}
