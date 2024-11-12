#include "../include/NOTGateIC.hpp"

NOTGateIC :: NOTGateIC() : IC(14, 14, 7, "NOT") {   
    cout << "NOTGateIC (Hex Inverter) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

void NOTGateIC :: simulate() {
    if (powerConnected && groundConnected) {
        // Inverting logic for each NOT gate
        pins[2 - 1] = !pins[1 - 1];   // Gate 1 (Pin 1 and Pin 2)
        pins[4 - 1] = !pins[3 - 1];   // Gate 2 (Pin 3 and Pin 4)
        pins[6 - 1] = !pins[5 - 1];   // Gate 3 (Pin 5 and Pin 6)
        pins[9 - 1] = !pins[8 - 1];   // Gate 4 (Pin 8 and Pin 9)
        pins[11 - 1] = !pins[10 - 1]; // Gate 5 (Pin 10 and Pin 11)
        pins[13 - 1] = !pins[12 - 1]; // Gate 6 (Pin 12 and Pin 13)
    } else
        throw runtime_error("NOTGateIC (Hex Inverter) is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}