#include <gtest/gtest.h>
#include "../src/IC.cpp"
#include "../src/Wire.cpp"

// Concrete IC class for testing that implements simulate()
template <typename T>
class TestIC : public IC<T> {
public:
    // Use the base class constructor
    TestIC(int pinCount, int vccPin, int groundPin, const string& name = "TestIC") 
        : IC<T>(pinCount, vccPin, groundPin, name) {}

    // Concrete implementation of simulate()
    void simulate() override {
        // Dummy implementation for testing
        // Could be empty or do a basic simulation
        for (int i = 1; i <= this->pinCount; ++i) {
            this->setPin(i, T(0));  // Reset all pins
        }
    }
};


// Test fixture for IC class
class ICTest : public ::testing::Test {
protected:
    // Create different TestICs for testing
    TestIC<int> intIC{10, 5, 9, "TestIntIC"};
    TestIC<float> floatIC{8, 4, 7, "TestFloatIC"};
    TestIC<bool> boolIC{6, 3, 6, "TestBoolIC"};
};

// Test IC Constructor and Basic Initialization
TEST_F(ICTest, ConstructorAndInitialization) {
    EXPECT_EQ(intIC.getTotalPins(), 10);
    EXPECT_EQ(intIC.getVccPin(), 5);
    EXPECT_EQ(intIC.getGroundPin(), 9);
    EXPECT_EQ(intIC.getName(), "TestIntIC");
}

// Test Pin Setting and Getting
TEST_F(ICTest, PinSetAndGet) {
    // Integer IC
    intIC.setPin(2, 42);
    EXPECT_EQ(intIC.getPin(2), 42);
    
    // Float IC
    floatIC.setPin(3, 3.14f);
    EXPECT_FLOAT_EQ(floatIC.getPin(3), 3.14f);
    
    // Bool IC
    boolIC.setPin(4, true);
    EXPECT_TRUE(boolIC.getPin(4));
}

// Test Invalid Pin Access
TEST_F(ICTest, InvalidPinAccess) {
    EXPECT_THROW(intIC.setPin(0, 10), out_of_range);
    EXPECT_THROW(intIC.setPin(11, 10), out_of_range);
    EXPECT_THROW(intIC.getPin(0), out_of_range);
    EXPECT_THROW(intIC.getPin(11), out_of_range);
}

// Test Power and Ground Connection
TEST_F(ICTest, PowerAndGroundConnection) {
    EXPECT_NO_THROW(intIC.connectVCC());
    EXPECT_THROW(intIC.connectVCC(), runtime_error);  // Double VCC connection
    
    EXPECT_NO_THROW(intIC.connectGround());
    
    // Ground connection without VCC should throw
    TestIC<int> newIC{5, 3, 4, "PowerlessIC"};
    EXPECT_THROW(newIC.connectGround(), runtime_error);
}

// Test Simulate Method
TEST_F(ICTest, SimulateMethod) {
    // Set some pins to non-zero values
    intIC.setPin(1, 10);
    intIC.setPin(3, 20);
    
    // Call simulate() which should reset all pins
    EXPECT_NO_THROW(intIC.simulate());
    
    // Check that all pins are reset
    for (int i = 1; i <= intIC.getTotalPins(); ++i) {
        EXPECT_EQ(intIC.getPin(i), 0);
    }
}

// Test Operator Overloading
TEST_F(ICTest, OperatorOverloading) {
    // Indexing operator
    intIC.setPin(3, 123);
    EXPECT_EQ(intIC[3], 123);
    
    // Equality operator
    TestIC<int> anotherIntIC{10, 5, 9, "AnotherTestIC"};
    intIC.setPin(1, 10);
    anotherIntIC.setPin(1, 10);
    EXPECT_FALSE(intIC == anotherIntIC);
    
    // Connection operator
    TestIC<int> destIC{8, 4, 7, "DestinationIC"};
    EXPECT_NO_THROW(intIC(1, destIC, 2));
    
    // Reset operator
    intIC.setPin(1, 42);
    !intIC;
    EXPECT_EQ(intIC[1], 0);
    
    // VCC/GND connection operator
    TestIC<int> powerIC{5, 3, 4, "PowerIC"};
    EXPECT_NO_THROW(powerIC += "VCC");
    EXPECT_NO_THROW(powerIC += "GND");
}

// Wire Connection Test
TEST_F(ICTest, WireConnection) {
    TestIC<int> sourceIC{5, 3, 4, "SourceIC"};
    TestIC<int> destIC{5, 3, 4, "DestinationIC"};
    
    sourceIC.setPin(2, 42);
    
    Wire<int> wire(&sourceIC, 2, &destIC, 3);
    
    EXPECT_NO_THROW(wire.connect());
    EXPECT_EQ(destIC.getPin(3), 42);
    
    EXPECT_NO_THROW(wire.disconnect());
    EXPECT_EQ(destIC.getPin(3), 0);
}

// Test Invalid Wire Creation
TEST_F(ICTest, InvalidWireConnection) {
    TestIC<int> sourceIC{5, 3, 4, "SourceIC"};
    
    // Wire to nullptr should throw
    EXPECT_THROW(Wire<int>(&sourceIC, 2, nullptr, 3), runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}