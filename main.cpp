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
#include <memory>

// Template for validating user input
template <typename T>
bool validateInput(T input, T minValue, T maxValue) {
    return input >= minValue && input <= maxValue;
}

// Template for setting pin values
template <typename T>
void setPinValue(T& ic, int pin, bool value) {
    if (validateInput(pin, 1, ic.getTotalPins())) {
        ic.setPin(pin, value);
        cout << "Pin " << pin << " on IC set to " << value << endl;
    } else {
        cout << "Invalid pin number!" << endl;
    }
}

// Template for connecting pins between two ICs
template <typename T1, typename T2>
void connectICs(T1& srcIC, int srcPin, T2& destIC, int destPin) {
    if (validateInput(srcPin, 1, srcIC.getTotalPins()) &&
        validateInput(destPin, 1, destIC.getTotalPins())) {
        destIC.setPin(destPin, srcIC.getPin(srcPin));
        cout << "Connected IC " << srcIC.getName() << " pin " << srcPin
             << " to IC " << destIC.getName() << " pin " << destPin << endl;
    } 
    
    else {
        cout << "Invalid pin connection!" << endl;
    }
}

// Function to display the main menu
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

// Function to create a new IC
template <typename T>
IC<T>* createIC() {
    cout << "Select IC type:\n";
    cout << "1. AND Gate\n2. OR Gate\n3. NOT Gate\n4. XOR Gate\n5. NAND Gate\n6. NOR Gate\n7. XNOR Gate\n";
    int icType;
    cin >> icType;

    IC<T>* newIC = nullptr;
    switch (icType) {
        case 1: newIC = new ANDGateIC<T>(); break;
        case 2: newIC = new ORGateIC<T>(); break;
        case 3: newIC = new NOTGateIC<T>(); break;
        case 4: newIC = new XORGateIC<T>(); break;
        case 5: newIC = new NANDGateIC<T>(); break;
        case 6: newIC = new NORGateIC<T>(); break;
        case 7: newIC = new XNORGateIC<T>(); break;
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

// Function to view available ICs
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

// Function to cleanup resources
template <typename T>
void cleanup(vector<IC<T>*>& icList, vector<Wire<T>*>& wireList) {
    for (IC<T>* ic : icList) delete ic;
    for (Wire<T>* wire : wireList) delete wire;
}


int main() {
    vector<IC<int>*> icList;
    vector<Wire<int>*> wireList;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: // View ICs
                viewICs(icList);
                break;

            case 2: { // Create a new IC
                IC<int>* newIC = createIC<int>();
                if (newIC) {
                    icList.push_back(newIC);
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

                if (pin < 1 || pin > selectedIC -> getTotalPins()) {
                    cout << "Invalid pin number.\n";
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
                cout << "Enter source pin: ";
                cin >> srcPin;

                cout << "Select destination IC index (1-" << icList.size() << "): ";
                cin >> destIC;
                cout << "Enter destination pin: ";
                cin >> destPin;

                if (!validateInput(srcIC, size_t(1), icList.size()) ||
                    !validateInput(destIC, size_t(1), icList.size())) {
                    cout << "Invalid IC index.\n";
                    break;
                }

                connectICs(*icList[srcIC - 1], srcPin, *icList[destIC - 1], destPin);
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
                if (icIndex < 1 || icIndex > icList.size()) {
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
                if (icIndex < 1 || icIndex > icList.size()) {
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
                cout << "Exiting program...\n";
                cleanup(icList, wireList);
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
