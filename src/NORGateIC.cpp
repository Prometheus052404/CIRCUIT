#include "../include/NORGateIC.hpp"

template <typename T>
NORGateIC<T> :: NORGateIC() : IC<T>(14, 14, 7 , "NOR") {
    cout << "NOR Gate IC (7402) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

template <typename T>
void NORGateIC<T> :: simulate() {
    if ((this -> powerConnected) && (this -> groundConnected)) {
        this -> pins[1 - 1] = !(this -> pins[3 - 1] | this -> pins[2 - 1]);    // Gate 1 (inputs on pins 3, 2; output on pin 1)
        this -> pins[4 - 1] = !(this -> pins[6 - 1] | this -> pins[5 - 1]);    // Gate 2 (inputs on pins 6, 5; output on pin 4)
        this -> pins[10 - 1] = !(this -> pins[8 - 1] | this -> pins[9 - 1]);   // Gate 3 (inputs on pins 9, 8; output on pin 10)
        this -> pins[13 - 1] = !(this -> pins[11 - 1] | this -> pins[12 - 1]); // Gate 4 (inputs on pins 12, 11; output on pin 13)
    } 
    else
        throw runtime_error("NOR Gate IC is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}
