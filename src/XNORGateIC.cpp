#include "../include/XNORGateIC.hpp"

template <typename T>
XNORGateIC<T> :: XNORGateIC() : IC<T>(14, 14, 7, "XNOR") {  // VCC on pin 14, GND on pin 7
    cout << "XNOR Gate IC (74266) created with 14pins, VCC on pin 14, GND on pin 7." << endl;
}

template <typename T>
void XNORGateIC<T> :: simulate() {
    if ((this -> powerConnected) && (this -> groundConnected)) {
        
        this -> pins[3 - 1] = (this -> pins[1 - 1] == this -> pins[2 - 1]) ? 1 : 0; // Gate 1: pins 1 and 2 are inputs, pin 3 is the output
        this -> pins[6 - 1] = (this -> pins[4 - 1] == this -> pins[5 - 1]) ? 1 : 0; // Gate 2: pins 4 and 5 are inputs, pin 6 is the output
        this -> pins[10 - 1] = (this -> pins[8 - 1] == this -> pins[9 - 1]) ? 1 : 0; // Gate 3: pins 8 and 9 are inputs, pin 10 is the output
        this -> pins[13 - 1] = (this -> pins[11 - 1] == this -> pins[12 - 1]) ? 1 : 0; // Gate 4: pins 11 and 12 are inputs, pin 13 is the output
    } else
        throw runtime_error("XNOR Gate IC (74266) is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}
