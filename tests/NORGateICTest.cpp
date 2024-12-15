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

    norGate.setPin(1, false);
    norGate.setPin(2, false);
    EXPECT_NO_THROW(norGate.simulate());
    EXPECT_TRUE(norGate.getPin(3));

    norGate.setPin(1, true);
    norGate.setPin(2, false);
    norGate.simulate();
    EXPECT_FALSE(norGate.getPin(3));
}

TEST_F(NORGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(norGate.simulate(), std::runtime_error);
}
