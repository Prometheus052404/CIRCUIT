#include "../include/Wire.hpp"
#include "../include/IC.hpp"

/**
 * @brief Constructor for the Wire class.
 * 
 * This constructor initializes a wire connection between two ICs.
 * 
 * @tparam T Data type of the signal transmitted through the wire.
 * @param srcIC Pointer to the source IC.
 * @param srcPin Pin number of the source IC.
 * @param destIC Pointer to the destination IC.
 * @param destPin Pin number of the destination IC.
 */
template <typename T>
Wire<T> :: Wire(IC<T>* srcIC, int srcPin, IC<T>* destIC, int destPin)
    : sourceIC(srcIC), sourcePin(srcPin), destinationIC(destIC), destinationPin(destPin) {
        if (!sourceIC)
            throw runtime_error("Source IC cannot be null.");
    
        if (!destinationIC)
            throw runtime_error("Destination IC cannot be null.");
    }

/**
 * @brief Destructor for the Wire class.
 * 
 * This destructor disconnects the wire and prevents dangling pointers.
 * 
 * @tparam T Data type of the signal transmitted through the wire.
 */
template <typename T>
Wire<T> :: ~Wire() {
    disconnect();
    // cout << "Wire destructor called." << endl; // Add this to confirm the destructor is being called
}

/**
 * @brief Connects the source IC to the destination IC.
 * 
 * This function transfers the signal from the source IC's pin to the destination IC's pin.
 * 
 * @tparam T Data type of the signal transmitted through the wire.
 * @throws runtime_error If the source or destination IC is invalid.
 */
template <typename T>
void Wire<T> :: connect() {
    if (!sourceIC || !destinationIC)
        throw runtime_error("Invalid IC connection.");

    destinationIC -> setPin(destinationPin, sourceIC -> getPin(sourcePin));
    cout << "Connected pin " << sourcePin << " of IC " << sourceIC -> getName()
         << " to pin " << destinationPin << " of IC " << destinationIC -> getName() << endl;
}

/**
 * @brief Disconnects the wire connection.
 * 
 * This function resets the destination IC's pin value and prevents dangling pointers.
 * 
 * @tparam T Data type of the signal transmitted through the wire.
 */
template <typename T>
void Wire<T> :: disconnect() {
    if (destinationIC) {
        destinationIC -> setPin(destinationPin, 0); // Reset the pin
        cout << "Disconnected pin " << destinationPin << " of IC " << destinationIC -> getName() << endl; //Destructor Message
        destinationIC = nullptr; // To Prevent Dangling Pointer.
    }

    else
        cout << "No IC connected to disconnect." << endl;
}
