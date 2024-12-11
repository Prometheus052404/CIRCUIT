#ifndef WIRE_HPP
#define WIRE_HPP

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class IC; // Forward declaration to allow IC usage in Wire

template <typename T>
class Wire {
    IC<T>* sourceIC;
    int sourcePin;
    IC<T>* destinationIC;
    int destinationPin;

public:
    IC<T>* getSourceIC() const { return sourceIC; }
    IC<T>* getDestinationIC() const { return destinationIC; }
    Wire(IC<T>* srcIC, int srcPin, IC<T>* destIC, int destPin); 
    ~Wire();

    void connect();
    void disconnect();
};

#endif // WIRE_HPP
