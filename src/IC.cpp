#include "../include/IC.hpp"

template <typename T>
IC<T> :: IC(int pinCount, int vccPin, int groundPin, const string& name)
    : name(name), pins(pinCount, T()), pinCount(pinCount), vccPin(vccPin), groundPin(groundPin), powerConnected(false), groundConnected(false) {}

template <typename T>
IC<T> :: IC(int pinCount) : pinCount(pinCount), pins(pinCount, T()) {}

template <typename T>
int IC<T> :: getTotalPins() const {
        return pinCount;
    }

template <typename T>
void IC<T> :: connectVCC() {
    if (powerConnected)
        throw runtime_error("VCC already connected.");

    pins[vccPin - 1] = T(1);
    powerConnected = true;
}

template <typename T>
void IC<T> :: connectGround() {
    if (!powerConnected) 
        throw runtime_error("Connect VCC before connecting GND.");

    pins[groundPin - 1] = T(0);
    groundConnected = true;
}

template <typename T>
void IC<T> :: setPin(int pin, T value) {
    if ((pin >= 1) && (pin <= pinCount))
        pins[pin - 1] = value;
    else
        throw out_of_range("Invalid pin number");
}

template <typename T>
T IC<T> :: getPin(int pin) const {
    if ((pin >= 1) && (pin <= pinCount))
        return pins[pin - 1];
    else
        throw out_of_range("Invalid pin number");
}

template <typename T>
T& IC<T> :: operator[](int pinNumber) {
    if ((pinNumber >= 0) && (pinNumber < pinCount))
        return pins[pinNumber-1];
    else
        throw out_of_range("Invalid pin number");
}

template <typename T>
void IC<T> :: operator()(int pinOut, IC<T>& otherIC, int pinIn) {
    if (pinOut < 1 || pinOut > pinCount || pinIn < 1 || pinIn > otherIC.getTotalPins())
            throw out_of_range("Invalid pin connection");
        otherIC.setPin(pinIn, getPin(pinOut));
    }

template <typename T>
IC<T>& IC<T> :: operator += (const string& connection) {
    if (connection == "VCC")
        connectVCC();
    else if (connection == "GND")
        connectGround();

    return *this;
}

template <typename T>
bool IC<T> :: operator == (const IC<T>& other) const {
    if (pinCount != other.pinCount) 
        return false;

    for (int i = 0; i < pinCount; i++) 
        if (pins[i] != other.pins[i]) 
            return false;

    return true;
}

template <typename T>
IC<T>& IC<T> :: operator!() {
    for (int i = 0; i < pinCount; i++)
        pins[i] = T(0);

    return *this;
}

// Explicit instantiations
template class IC<int>;
template class IC<float>;
template class IC<bool>;