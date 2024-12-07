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
    //get function
    IC* getSourceIC() const { return sourceIC; }
    int getSourcePin() const { return sourcePin; }
    IC* getDestinationIC() const { return destinationIC; }
    int getDestinationPin() const { return destinationPin; }
    Wire(IC* srcIC, int srcPin, IC* destIC, int destPin);
    ~Wire();

    void connect();
    void disconnect();
};

#endif // WIRE_HPP
