#ifndef WIRE_HPP
#define WIRE_HPP

#include <iostream>
#include <string>
using namespace std;

class IC; // Forward declaration to allow IC usage in Wire

class Wire {
private:
    IC* sourceIC;
    int sourcePin;
    IC* destinationIC;
    int destinationPin;

public:
    Wire(IC* srcIC, int srcPin, IC* destIC, int destPin);
    ~Wire();

    void connect();
    void disconnect();
};

#endif // WIRE_HPP
