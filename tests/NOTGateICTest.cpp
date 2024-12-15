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

    notGate.setPin(1, true);
    EXPECT_NO_THROW(notGate.simulate());
    EXPECT_FALSE(notGate.getPin(2));

    notGate.setPin(1, false);
    notGate.simulate();
    EXPECT_TRUE(notGate.getPin(2));
}

TEST_F(NOTGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(notGate.simulate(), std::runtime_error);
}
