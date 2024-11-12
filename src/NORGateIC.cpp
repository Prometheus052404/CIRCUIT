#include "../include/NORGateIC.hpp"

NORGateIC :: NORGateIC() : IC(14, 14, 7 , "NOR") {
    cout << "NOR Gate IC (7402) created with 14 pins, VCC on pin 14, GND on pin 7." << endl;
}

void NORGateIC :: simulate() {
    if (powerConnected && groundConnected) {
        pins[3 - 1] = !(pins[1 - 1] | pins[2 - 1]); // Gate 1 (Pins 1, 2 => Output on Pin 3)
        pins[6 - 1] = !(pins[4 - 1] | pins[5 - 1]); // Gate 2 (Pins 4, 5 => Output on Pin 6)
        pins[10 - 1] = !(pins[8 - 1] | pins[9 - 1]); // Gate 3 (Pins 8, 9 => Output on Pin 10)
        pins[13 - 1] = !(pins[11 - 1] | pins[12 - 1]);  // Gate 4 (Pins 11, 12 => Output on Pin 13)
    } 
    else
        throw runtime_error("NOR Gate IC is not powered on."); //handling exceptions, this will throw an error if the VCC and the Ground are not conneted to the IC
}
