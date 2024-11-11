#include <iostream>
#include <stdexcept>

using namespace std;

class IC {
    friend class Breadboard;

protected:
    int* pins;            // Dynamic array to hold pin values
    int pinCount;         // Number of pins
    int vccPin;           // VCC pin number
    int groundPin;        // GND pin number
    bool powerConnected;
    bool groundConnected;

public:
    IC(int pinCount, int vccPin, int groundPin);
    virtual ~IC();

    void connectVCC();
    void connectGround();
    void setPin(int pin, int value);
    int getPin(int pin) const;

    int& operator[](int pinNumber);
    void operator()(int pinOut, IC& otherIC, int pinIn);
    IC& operator+=(const std::string& connection);
    bool operator==(const IC& other) const;
    IC& operator!();


    virtual void simulate() = 0; // Pure virtual function for IC-specific logic
};
