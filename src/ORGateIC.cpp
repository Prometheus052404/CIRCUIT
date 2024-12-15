#include "../include/ORGateIC.hpp"

template <typename T>
ORGateIC<T> :: ORGateIC() : IC<T>(14, 14, 7, "OR") {
    cout << "OR Gate IC (7432) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

template <typename T>
void ORGateIC<T> :: simulate() {
    if ((this -> powerConnected) && (this -> groundConnected)) {
        this -> pins[3 - 1] = this -> pins[1 - 1] | this -> pins[2 - 1];    // Gate 1 (inputs on pins 1, 2; output on pin 3)
        this -> pins[6 - 1] = this -> pins[4 - 1] | this -> pins[5 - 1];    // Gate 2 (inputs on pins 4, 5; output on pin 6)
        this -> pins[8 - 1] = this -> pins[9 - 1] | this -> pins[10 - 1];   // Gate 3 (inputs on pins 9, 10; output on pin 8)
        this -> pins[11 - 1] = this -> pins[12 - 1] | this -> pins[13 - 1]; // Gate 4 (inputs on pins 12, 13; output on pin 11)
    } 
    else
        throw runtime_error("OR Gate IC is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}
