#include "../include/IC.hpp"

IC :: IC(int pinCount, int vccPin, int groundPin, const string& name)
    : name(name), pinCount(pinCount), vccPin(vccPin), groundPin(groundPin), powerConnected(false), groundConnected(false) {
    pins = new int[pinCount]();
}

int IC :: getTotalPins() const {
        return pinCount;
    }

void IC :: connectVCC() {
    if (powerConnected)
        throw runtime_error("VCC already connected.");

    pins[vccPin - 1] = 1;
    powerConnected = true;
}

void IC :: connectGround() {
    if (!powerConnected) 
        throw runtime_error("Connect VCC before connecting GND.");

    pins[groundPin - 1] = 0;
    groundConnected = true;
}

void IC :: setPin(int pin, int value) {
    if ((pin >= 1) && (pin <= pinCount))
        pins[pin - 1] = value;
    else
        throw out_of_range("Invalid pin number");
}

int IC :: getPin(int pin) const {
    if ((pin >= 1) && (pin <= pinCount))
        return pins[pin - 1];
    else
        throw out_of_range("Invalid pin number");
}

int& IC :: operator[](int pinNumber) {
    if ((pinNumber >= 0) && (pinNumber < pinCount))
        return pins[pinNumber-1];
    else
        throw out_of_range("Invalid pin number");
}

void IC :: operator()(int pinOut, IC& otherIC, int pinIn) {
    otherIC.setPin(pinIn, getPin(pinOut));
}

IC& IC :: operator += (const string& connection) {
    if (connection == "VCC")
        connectVCC();
    else if (connection == "GND")
        connectGround();

    return *this;
}

bool IC :: operator == (const IC& other) const {
    if (pinCount != other.pinCount) 
        return false;

    for (int i = 0; i < pinCount; i++) 
        if (pins[i] != other.pins[i]) 
            return false;

    return true;
}

IC& IC :: operator!() {
    for (int i = 0; i < pinCount; i++)
        pins[i] = 0;

    return *this;
}