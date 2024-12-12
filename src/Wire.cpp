#include "../include/Wire.hpp"
#include "../include/IC.hpp"

template <typename T>
Wire<T> :: Wire(IC<T>* srcIC, int srcPin, IC<T>* destIC, int destPin)
    : sourceIC(srcIC), sourcePin(srcPin), destinationIC(destIC), destinationPin(destPin) {}

template <typename T>
Wire<T> :: ~Wire() {
    disconnect();
    // cout << "Wire destructor called." << endl; // Add this to confirm the destructor is being called
}

template <typename T>
void Wire<T> :: connect() {
    if (!sourceIC || !destinationIC) {
        throw runtime_error("Invalid IC connection.");
    }
    destinationIC -> setPin(destinationPin, sourceIC -> getPin(sourcePin));
    cout << "Connected pin " << sourcePin << " of IC " << sourceIC -> getName()
         << " to pin " << destinationPin << " of IC " << destinationIC -> getName() << endl;
}

template <typename T>
void Wire<T> :: disconnect() {
    if (destinationIC) {
        destinationIC -> setPin(destinationPin, 0); // Reset the pin
        cout << "Disconnected pin " << destinationPin << " of IC " << destinationIC -> getName() << endl;
        destinationIC = nullptr; // To Prevent Dangling Pointer.
    }

    else
        cout << "No IC connected to disconnect." << endl;
}
