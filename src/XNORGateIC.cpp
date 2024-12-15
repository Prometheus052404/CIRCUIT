#include "../include/XNORGateIC.hpp"

template <typename T>
XNORGateIC<T> :: XNORGateIC() : IC<T>(14, 14, 7, "XNOR") {  // VCC on pin 14, GND on pin 7
    cout << "XNOR Gate IC (74266) created with 14pins, VCC on pin 14, GND on pin 7." << endl;
}

template <typename T>
void XNORGateIC<T> :: simulate() {
    if ((this -> powerConnected) && (this -> groundConnected)) {
        
        this -> pins[3 - 1] = (this -> pins[1 - 1] == this -> pins[2 - 1]) ? 1 : 0;    // Gate 1 (inputs on pins 1, 2; output on pin 3)
        this -> pins[4 - 1] = (this -> pins[6 - 1] == this -> pins[5 - 1]) ? 1 : 0;    // Gate 2 (inputs on pins 6, 5; output on pin 4)
        this -> pins[10 - 1] = (this -> pins[8 - 1] == this -> pins[9 - 1]) ? 1 : 0;   // Gate 3 (inputs on pins 9, 8; output on pin 10)
        this -> pins[11 - 1] = (this -> pins[13 - 1] == this -> pins[12 - 1]) ? 1 : 0; // Gate 4 (inputs on pins 12, 13; output on pin 11)
    } 
    else
        throw runtime_error("XNOR Gate IC (74266) is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}
