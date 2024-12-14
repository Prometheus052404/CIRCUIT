/* 
Project done by Team-64 (CS23I1027 - Harith Yerragolam and CS23I1064 - Parth Pandey)
https://github.com/Prometheus052404/CIRCUIT
*/

#include "./src/ANDGateIC.cpp"
#include "./src/ORGateIC.cpp"
#include "./src/NOTGateIC.cpp"
#include "./src/XORGateIC.cpp"
#include "./src/NANDGateIC.cpp"
#include "./src/NORGateIC.cpp"
#include "./src/XNORGateIC.cpp"
#include "./src/Wire.cpp"
#include "./include/CustomExceptions.hpp"
#include <memory>
#include <limits>

/**
 * @brief Validates user input for an integer within a given range.
 * 
 * This function ensures that user input is a valid integer within the specified range.
 * It prompts the user to re-enter the input if it's invalid.
 * 
 * @param min The minimum acceptable value.
 * @param max The maximum acceptable value.
 * 
 * @return int A valid user input within the range [min, max].
 */
template <typename T>
bool validateInput(T input, T minValue, T maxValue) {
    return input >= minValue && input <= maxValue;
}

/**
 * @brief Sets the value of a pin for a specific IC.
 * 
 * This function prompts the user to enter the IC index, pin number, and pin value.
 * It sets the value of the specified pin for the selected IC.
 * 
 * @param icList A vector containing pointers to all created ICs.
 */
template <typename T>
void setPinValue(T& ic, int pin, bool value) {
    if (!validateInput(pin, 1, ic.getTotalPins())) {
        cerr << "Error: Invalid pin number " << pin
             << ". Valid range is 1 to " << ic.getTotalPins() << ".\n";
        return;
    }

    if (pin == ic.getVccPin() || pin == ic.getGroundPin()) {
        cerr << "Error: Cannot manually set values for VCC (pin "
             << ic.getVccPin() << ") or GND (pin " << ic.getGroundPin() << ").\n";
        return;
    }

    ic.setPin(pin, value);
    cout << "Pin " << pin << " on IC set to value " << value << ".\n";
}

/**
 * @brief Connects two ICs by creating a wire between them.
 * 
 * This function prompts the user to enter the indices and pins of two ICs to be connected.
 * It creates a wire that transmits the signal from the source IC pin to the destination IC pin.
 * 
 * @param icList A vector containing pointers to all created ICs.
 * @param wireList A vector containing pointers to all created wires.
 */
template <typename T1, typename T2>
void connectICs(T1& srcIC, int srcPin, T2& destIC, int destPin) {
    if (!validateInput(srcPin, 1, srcIC.getTotalPins())) {
        cerr << "Error: Source pin " << srcPin
             << " is invalid. Valid range is 1 to " << srcIC.getTotalPins() << ".\n";
        return;
    }
    if (!validateInput(destPin, 1, destIC.getTotalPins())) {
        cerr << "Error: Destination pin " << destPin
             << " is invalid. Valid range is 1 to " << destIC.getTotalPins() << ".\n";
        return;
    }

    if (srcPin == srcIC.getVccPin() || srcPin == srcIC.getGroundPin() ||
        destPin == destIC.getVccPin() || destPin == destIC.getGroundPin()) {
        cerr << "Error: Cannot connect VCC or GND pins directly. Please choose valid data pins.\n";
        return;
    }

    // Proceed with connection
    destIC.setPin(destPin, srcIC.getPin(srcPin));
    cout << "Connected IC " << srcIC.getName() << " pin " << srcPin
         << " to IC " << destIC.getName() << " pin " << destPin << ".\n";
}

/**
 * @brief Displays the main menu and gets the user's choice.
 * 
 * This function displays a list of options for the user to select from.
 * It validates the user input and ensures a valid choice is returned.
 * 
 * @return int The user's choice from the menu.
 */
void displayMenu() {
    cout << "\n-----------------------------------\n";
    cout << "--- Circuit Simulator Menu ---\n";
    cout << "1. View ICs\n";
    cout << "2. Create a new IC\n";
    cout << "3. Set pin values\n";
    cout << "4. Connect ICs with a wire\n";
    cout << "5. Simulate IC\n";
    cout << "6. Connect Power and Ground\n";
    cout << "7. View IC pin states\n";
    cout << "8. Exit\n";
    cout << "-----------------------------------\n";
    cout << "Enter your choice: ";
}

/**
 * @brief Creates a new IC based on user input.
 * 
 * This function prompts the user to select the type of IC to create (AND, OR, NOT, etc.).
 * It dynamically creates the selected IC and returns a pointer to it.
 * 
 * @return IC<int>* Pointer to the newly created IC.
 */
template <typename T>
unique_ptr<IC<T>> createIC() {
    cout << "Select IC type:\n";
    cout << "1. AND Gate\n2. OR Gate\n3. NOT Gate\n4. XOR Gate\n5. NAND Gate\n6. NOR Gate\n7. XNOR Gate\n";
    int icType;
    cout << "Enter IC number: "; 
    cin >> icType;

    unique_ptr<IC<T>> newIC = nullptr;
    switch (icType) {
        case 1: newIC = make_unique<ANDGateIC<T>>();  break;
        case 2: newIC = make_unique<ORGateIC<T>>(); break;
        case 3: newIC = make_unique<NOTGateIC<T>>(); break;
        case 4: newIC = make_unique<XORGateIC<T>>(); break;
        case 5: newIC = make_unique<NANDGateIC<T>>(); break;
        case 6: newIC = make_unique<NORGateIC<T>>(); break;
        case 7: newIC = make_unique<XNORGateIC<T>>(); break;
        default: cout << "Invalid choice.\n"; return nullptr;
    }

    string powerChoice;
    cout << "Connect power to this IC? (y/n): ";
    cin >> powerChoice;

    if (powerChoice == "y" || powerChoice == "Y") {
        newIC->connectVCC();
        newIC->connectGround();
        cout << "Power connected to IC.\n";
    }

    return newIC;
}

/**
 * @brief Displays the details of all created ICs and their pin states.
 * 
 * This function iterates through the list of ICs and prints each IC's type, pin numbers, and their corresponding values.
 * 
 * @param icList A vector containing pointers to all created ICs.
 */
template <typename T>
void viewICs(const vector<IC<T>*>& icList) {
    if (icList.empty()) {
        cout << "No ICs available.\n";
        return;
    }

    cout << "ICs available: \n";
    for (size_t i = 0; i < icList.size(); ++i) {
        cout << i + 1 << ". " << icList[i]->getName() << endl;
    }
}

/**
 * @brief Cleans up all dynamically allocated memory for ICs and wires.
 * 
 * This function iterates through the lists of ICs and wires, deallocating the memory associated with each of them.
 * 
 * @param icList A vector containing pointers to all created ICs.
 * @param wireList A vector containing pointers to all created wires.
 */
template <typename T>
void cleanup(vector<IC<T>*>& icList, vector<Wire<T>*>& wireList) {
    for (Wire<T>* wire : wireList) {
        delete wire;
        wire = nullptr;
    }
    wireList.clear();

    for (IC<T>* ic : icList) {
        delete ic;
        ic = nullptr;
    }
    icList.clear();

    cout << "All resources cleaned up successfully.\n";
}

/**
 * @brief Main entry point for the digital circuit simulator.
 * 
 * This function initializes the menu-driven interface for creating, managing, and simulating ICs and wires.
 * It allows users to create ICs, set pin values, connect wires, view ICs, and clean up allocated resources.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {
    vector<IC<int>*> icList;
    vector<Wire<int>*> wireList;

    while (true) {
        displayMenu();
        int choice;
        while (true) {
            cout << "Enter your choice: ";
            if (cin >> choice) break;
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }       


        switch (choice) {
            case 1: // View ICs
                viewICs(icList);
                break;

            case 2: { // Create a new IC
                unique_ptr<IC<int>> newIC = createIC<int>();
                if (newIC) {
                    icList.push_back(newIC.release());
                    cout << "IC created and added to the circuit.\n";
                }
                break;
            }

            case 3: { // Set pin values
                if (icList.empty()) {
                    cout << "No ICs available. Create an IC first.\n";
                    break;
                }

                viewICs(icList);
                size_t icIndex;
                int pin, value;
                cout << "Select IC index (1-" << icList.size() << "): ";
                cin >> icIndex;

                if (!validateInput(icIndex, size_t(1), icList.size())) {
                    cout << "Invalid IC index.\n";
                    break;
                }

                IC<int>* selectedIC = icList[icIndex - 1];
                cout << "Pin values of IC " << icIndex << ":\n";
                for (int pin = 1; pin <= selectedIC -> getTotalPins(); ++pin)
                    cout << "Pin " << pin << ": " << selectedIC -> getPin(pin) << " ";
    
                cout << "\n-----------------------------------\n";
                cout << "Enter pin number to set (1-" << selectedIC -> getTotalPins() << "): ";
                cin >> pin;

                if (!validateInput<size_t>(pin, size_t(1), selectedIC -> getTotalPins())) {
                    throw InvalidPinException();
                    continue;
                }
                
                else if ((pin == selectedIC -> getVccPin()) || (pin == selectedIC -> getGroundPin())) {
                    cout << "Cannot set VCC or GND pin value.\n";
                    continue;
                }

                cout << "Enter value for pin " << pin << " (0/1): ";
                cin >> value;

                try {
                    selectedIC -> setPin(pin, value);
                    //changing values for pins connected by wire without accessing the private members  
                    for (Wire<int>* wire : wireList) {
                        if (wire -> getSourceIC() == selectedIC && wire -> getSourcePin() == pin)
                            wire -> connect();
                    }

                    cout << "Pin value set successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }

                setPinValue(*selectedIC, pin, value);
                break;
            }

            case 4: { // Connect ICs with a wire
                if (icList.size() < 2) {
                    cout << "At least two ICs are required for connection.\n";
                    break;
                }

                viewICs(icList);
                size_t srcIC, destIC;
                int srcPin, destPin;
                cout << "Select source IC index (1-" << icList.size() << "): ";
                cin >> srcIC;
                cout << "Pin values of IC " << srcIC << ":\n";
                for (int pin = 1; pin <= icList[srcIC - 1] -> getTotalPins(); ++pin)
                    cout << "Pin " << pin << ": " << icList[srcIC - 1] -> getPin(pin) << " ";

                cout << "\n-----------------------------------\n";
                cout << "Enter source pin: ";
                cin >> srcPin;

                cout << "Select destination IC index (1-" << icList.size() << "): ";
                cin >> destIC;

                cout << "Pin values of IC " << destIC << ":\n";
                for (int pin = 1; pin <= icList[destIC - 1] -> getTotalPins(); ++pin)
                    cout << "Pin " << pin << ": " << icList[destIC - 1] -> getPin(pin) << " ";

                cout << "\n-----------------------------------\n";

                cout << "Enter destination pin: ";
                cin >> destPin;

                if (!validateInput(srcIC, size_t(1), icList.size()) ||
                    !validateInput(destIC, size_t(1), icList.size())) {
                    cout << "Invalid IC index.\n";
                    break;
                }

                // Pin-based connection, Static Binding i.e. One time connection.
                connectICs(*icList[srcIC - 1], srcPin, *icList[destIC - 1], destPin);

                // Wire-based connection, Live update of pin values will be reflected.
                try {
                    Wire<int>* newWire = new Wire(icList[srcIC - 1], srcPin, icList[destIC - 1], destPin);
                    newWire -> connect();
                    wireList.push_back(newWire);
                    cout << "Wire connected successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }

                break;
            } 
        
            case 5: { // Simulate IC
                if (icList.empty()) {
                    cout << "No ICs available to simulate.\n";
                    break;
                }

                size_t icIndex;
                cout << "ICs available: \n";
                for (size_t i = 0; i < icList.size(); ++i) {
                    cout << i + 1 << ". " << icList[i]->getName() << endl;
                }

                cout << "Select IC index to simulate (1-" << icList.size() << "): ";
                cin >> icIndex;
                if (!validateInput(icIndex, size_t(1), icList.size())) {
                    cout << "Invalid IC index.\n";
                    break;
                }

                try {
                    icList[icIndex - 1]->simulate();
                    cout << "IC simulation completed successfully.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }

            case 6: { // Connect Power and Ground
                if (icList.empty()) {
                    cout << "No ICs available to connect power and ground.\n";
                    break;
                }

                size_t icIndex;
                cout << "ICs available: \n";
                for (size_t i = 0; i < icList.size(); ++i) {
                    cout << i + 1 << ". " << icList[i]->getName() << endl;
                }

                cout << "Select IC index to connect power and ground (1-" << icList.size() << "): ";
                cin >> icIndex;
                if (!validateInput(icIndex, size_t(1), icList.size())) {
                    cout << "Invalid IC index.\n";
                    break;
                }

                try {
                    icList[icIndex - 1]->connectVCC();
                    icList[icIndex - 1]->connectGround();
                    cout << "Power and ground connected to IC.\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            
            case 7: { // View IC pin states
                if (icList.empty()) {
                    cout << "No ICs available to view.\n";
                    break;
                }

                for (size_t i = 0; i < icList.size(); ++i) {
                    cout << "IC " << i + 1 << " (" << icList[i]->getName() << "): ";
                    for (int pin = 1; pin <= icList[i]->getTotalPins(); ++pin) {
                        try {
                            cout << "Pin " << pin << ": " << icList[i]->getPin(pin) << " ";

                        } catch (const exception&) {
                            cout << "N/A ";
                        }
                    }
                    cout << endl;
                }
                break;
            }

            case 8: // Exit
                cout << "Exiting program..." << endl;
                cleanup(icList, wireList);
                cout << "All ICs and wires have been deleted. Program terminated." << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

template class ANDGateIC<int>;
template class ORGateIC<int>;
template class NOTGateIC<int>;
template class XORGateIC<int>;
template class NANDGateIC<int>;
template class NORGateIC<int>;
template class XNORGateIC<int>;
template class Wire<int>;
