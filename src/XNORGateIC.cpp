#include "../include/XNORGateIC.hpp"

XNORGateIC :: XNORGateIC() : IC(14, 14, 7, "XNOR") {  // VCC on pin 14, GND on pin 7
    cout << "XNOR Gate IC (74266) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

void XNORGateIC :: simulate() {
    if (powerConnected && groundConnected) {
        
        pins[3 - 1] = (pins[1 - 1] == pins[2 - 1]) ? 1 : 0; // Gate 1: Pins 1 and 2 are inputs, pin 3 is the output
        pins[6 - 1] = (pins[4 - 1] == pins[5 - 1]) ? 1 : 0; // Gate 2: Pins 4 and 5 are inputs, pin 6 is the output
        pins[10 - 1] = (pins[8 - 1] == pins[9 - 1]) ? 1 : 0; // Gate 3: Pins 8 and 9 are inputs, pin 10 is the output
        pins[13 - 1] = (pins[11 - 1] == pins[12 - 1]) ? 1 : 0; // Gate 4: Pins 11 and 12 are inputs, pin 13 is the output
    } else
        throw runtime_error("XNOR Gate IC (74266) is not powered on.");
}
