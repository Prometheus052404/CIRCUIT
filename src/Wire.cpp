#include "../include/Wire.hpp"
#include "../include/IC.hpp"

Wire :: Wire(IC* srcIC, int srcPin, IC* destIC, int destPin)
    : sourceIC(srcIC), sourcePin(srcPin), destinationIC(destIC), destinationPin(destPin) {}

Wire :: ~Wire() {
    disconnect();
}

void Wire :: connect() {
    if (!sourceIC || !destinationIC) {
        throw runtime_error("Invalid IC connection.");
    }
    destinationIC->setPin(destinationPin, sourceIC->getPin(sourcePin));
    cout << "Connected pin " << sourcePin << " of IC " << sourceIC->getName()
         << " to pin " << destinationPin << " of IC " << destinationIC->getName() << endl;
}

void Wire :: disconnect() {
    if (destinationIC) {
        destinationIC->setPin(destinationPin, 0); // Reset the pin
        cout << "Disconnected pin " << destinationPin << " of IC " << destinationIC->getName() << endl;
    }
}
