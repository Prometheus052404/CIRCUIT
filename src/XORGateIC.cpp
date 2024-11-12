#include "../include/XORGateIC.hpp"

XORGateIC :: XORGateIC() : IC(14, 14, 7, "XOR") {
    cout << "XOR Gate IC (7486) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

void XORGateIC :: simulate() {
    if (powerConnected && groundConnected) {
        pins[3 - 1] = pins[1 - 1] ^ pins[2 - 1];    // Gate 1
        pins[6 - 1] = pins[4 - 1] ^ pins[5 - 1];    // Gate 2
        pins[8 - 1] = pins[9 - 1] ^ pins[10 - 1];   // Gate 3
        pins[11 - 1] = pins[12 - 1] ^ pins[13 - 1]; // Gate 4
    } else
        throw runtime_error("XOR Gate IC is not powered on.");
}
