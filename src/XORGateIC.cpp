#include "../include/XORGateIC.hpp"

template <typename T>
XORGateIC<T> :: XORGateIC() : IC<T>(14, 14, 7, "XOR") {
    cout << "XOR Gate IC (7486) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

template <typename T>
void XORGateIC<T> :: simulate() {
    if (this -> powerConnected && this -> groundConnected) {
        this -> pins[3 - 1] = this -> pins[1 - 1] ^ this -> pins[2 - 1];    // Gate 1
        this -> pins[6 - 1] = this -> pins[4 - 1] ^ this -> pins[5 - 1];    // Gate 2
        this -> pins[8 - 1] = this -> pins[9 - 1] ^ this -> pins[10 - 1];   // Gate 3
        this -> pins[11 - 1] = this -> pins[12 - 1] ^ this -> pins[13 - 1]; // Gate 4
    } else
        throw runtime_error("XOR Gate IC is not powered on.");
}
