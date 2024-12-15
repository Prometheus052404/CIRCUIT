#include <gtest/gtest.h>
#include "../src/NANDGateIC.cpp"

class NANDGateICTest : public ::testing::Test {
protected:
    NANDGateIC<bool> nandGate;
};

TEST_F(NANDGateICTest, Constructor) {
    EXPECT_EQ(nandGate.getTotalPins(), 14);
    EXPECT_EQ(nandGate.getName(), "NAND");
}

TEST_F(NANDGateICTest, Simulate) {
    nandGate.connectVCC();
    nandGate.connectGround();

    // Test pin pair (1, 2) -> (3)
    nandGate.setPin(1, true);
    nandGate.setPin(2, true);
    nandGate.simulate();
    EXPECT_FALSE(nandGate.getPin(3));

    nandGate.setPin(1, false);
    nandGate.setPin(2, false);
    nandGate.simulate();
    EXPECT_TRUE(nandGate.getPin(3));

    // Test pin pair (4, 5) -> (6)
    nandGate.setPin(4, false);
    nandGate.setPin(5, false);
    nandGate.simulate();
    EXPECT_TRUE(nandGate.getPin(6));

    nandGate.setPin(4, true);
    nandGate.setPin(5, true);
    nandGate.simulate();
    EXPECT_FALSE(nandGate.getPin(6));

    // Test pin pair (9, 10) -> (8)
    nandGate.setPin(9, false);
    nandGate.setPin(10, false);
    nandGate.simulate();
    EXPECT_TRUE(nandGate.getPin(8));

    // Test pin pair (12, 13) -> (11)
    nandGate.setPin(12, true);
    nandGate.setPin(13, true);
    nandGate.simulate();
    EXPECT_FALSE(nandGate.getPin(11));
}

TEST_F(NANDGateICTest, SimulateWithoutPower) {
    EXPECT_THROW(nandGate.simulate(), std::runtime_error);
}
