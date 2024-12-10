/* 
Project done by Team-64 (CS23I1027 - Harith Yerragolam and CS23I1064 - Parth Pandey)
https://github.com/Prometheus052404/CIRCUIT
*/

#include "./include/ANDGateIC.hpp"
#include "./include/ORGateIC.hpp"
#include "./include/NOTGateIC.hpp"
#include "./include/XORGateIC.hpp"
#include "./include/NANDGateIC.hpp"
#include "./include/NORGateIC.hpp"
#include "./include/XNORGateIC.hpp"
#include "./include/Wire.hpp"
#include <string>
#include <vector>

int main() {
    vector<IC*> icList;
    vector<Wire*> wireList;

    while (true) {
        //making a box for the menu
        cout << "\n-----------------------------------\n";
        cout << "\n--- Circuit Simulator Menu ---\n";
        cout << "1. View ICs\n";
        cout << "2. Create a new IC\n";
        cout << "3. Set pin values\n";
        cout << "4. Connect ICs with a wire\n";
        cout << "5. Simulate IC\n";
        cout << "6. Connect Power and Ground\n";
        cout << "7. View IC pin states\n";
        cout << "8. Exit\n";

        cout << "-----------------------------------\n";

        //taking the input from the user
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (icList.empty()) {
                cout << "No ICs available.\n";
                continue;
            }

            cout << "ICs available: \n";
            for (size_t i = 0; i < icList.size(); ++i) {
                cout << i + 1 << ". " << icList[i]  ->  getName() << endl;
            }
        }
        else if (choice == 2) {
            cout << "Select IC type:\n";
            cout << "1. AND Gate\n2. OR Gate\n3. NOT Gate\n4. XOR Gate\n5. NAND Gate\n6. NOR Gate\n7. XNOR Gate\n";
            int icType;
            cin >> icType;

            IC* newIC = nullptr;
            switch (icType) {
                case 1: newIC = new ANDGateIC(); break;
                case 2: newIC = new ORGateIC(); break;
                case 3: newIC = new NOTGateIC(); break;
                case 4: newIC = new XORGateIC(); break;
                case 5: newIC = new NANDGateIC(); break;
                case 6: newIC = new NORGateIC(); break;
                case 7: newIC = new XNORGateIC(); break;
                default: cout << "Invalid choice.\n"; continue;
            }

            string powerChoice;
            cout << "Connect power to this IC? (y/n): ";
            cin >> powerChoice;

            if (powerChoice == "y" || powerChoice == "Y") {
                newIC -> connectVCC();
                newIC -> connectGround();
                cout << "Power connected to IC.\n";
            }

            icList.push_back(newIC);
            cout << "IC created and added to the circuit.\n";
        }

        else if (choice == 3) {
            if (icList.empty()) {
                cout << "No ICs available. Create an IC first.\n";
                continue;
            }

            size_t icIndex;
            int pin, value;
            cout << "ICs available: \n";
            for (size_t i = 0; i < icList.size(); ++i)
                cout << i + 1 << ". " << icList[i] -> getName() << endl;

            cout<< "-----------------------------------\n";
            cout << "Select IC index (1-" << icList.size() << "): ";
            cin >> icIndex;
            if ((icIndex < 1) || (icIndex > icList.size())) {
                cout << "Invalid IC index.\n";
                continue;
            }

            IC* selectedIC = icList[icIndex - 1];
            cout << "Pin values of IC " << icIndex << ":\n";
            for (int pin = 1; pin <= selectedIC -> getTotalPins(); ++pin) {
                cout << "Pin " << pin << ": " << selectedIC -> getPin(pin) << " ";
            }
            cout << "\n-----------------------------------\n";
            cout << "Enter pin number to set (1-" << selectedIC -> getTotalPins() << "): ";
            cin >> pin;
            if (pin < 1 || pin > selectedIC -> getTotalPins()) {
                cout << "Invalid pin number.\n";
                continue;
            }
            else if ((pin == selectedIC -> vccPin) || (pin == selectedIC -> groundPin)) {
                cout << "Cannot set VCC or GND pin value.\n";
                continue;
            }
            cout << "Enter value for pin " << pin << " (0/1): ";
            cin >> value;

            try {
                selectedIC -> setPin(pin, value);
                //changing values for pins connected by wire without accessing the private members  
                for (Wire* wire : wireList) {
                    if (wire -> getSourceIC() == selectedIC && wire -> getSourcePin() == pin)
                        wire -> connect();
                }

                cout << "Pin value set successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 4) {
            if (icList.size() < 2) {
                cout << "At least two ICs are required for connection.\n";
                continue;
            }

            size_t srcIC, destIC;
            int srcPin, destPin;
            cout << "ICs available: \n";
            for (size_t i = 0; i < icList.size(); ++i) {
                cout << i + 1 << ". " << icList[i] -> getName() << endl;
            }
            cout << "-----------------------------------\n";
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

            if (srcIC < 1 || srcIC > icList.size() || destIC < 1 || destIC > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            try {
                Wire* newWire = new Wire(icList[srcIC - 1], srcPin, icList[destIC - 1], destPin);
                newWire -> connect();
                wireList.push_back(newWire);
                cout << "Wire connected successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 5) {
            if (icList.empty()) {
                cout << "No ICs available to simulate.\n";
                continue;
            }

            size_t icIndex;
            cout << "ICs available: \n";
            for (size_t i = 0; i < icList.size(); ++i)
                cout << i + 1 << ". " << icList[i] -> getName() << endl;

            cout << "-----------------------------------\n";
            cout << "Select IC index to simulate (1-" << icList.size() << "): ";
            cin >> icIndex;
            if (icIndex < 1 || icIndex > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            try {
                icList[icIndex - 1] -> simulate();
                cout << "IC simulation completed successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 6) {
            if (icList.empty()) {
                cout << "No ICs available to connect power and ground.\n";
                continue;
            }

            size_t icIndex;
            cout << "ICs available: \n";
            for (size_t i = 0; i < icList.size(); ++i)
                cout << i + 1 << ". " << icList[i] -> getName() << endl;

            cout << "-----------------------------------\n";
            cout << "Select IC index to connect power and ground (1-" << icList.size() << "): ";
            cin >> icIndex;
            if (icIndex < 1 || icIndex > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            try {
                icList[icIndex - 1] -> connectVCC();
                icList[icIndex - 1] -> connectGround();
                cout << "Power and ground connected to IC.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 7) {
            if (icList.empty()) {
                cout << "No ICs available to view.\n";
                continue;
            }

            for (size_t i = 0; i < icList.size(); ++i) {
                cout << "IC " << i + 1 << " (" << icList[i] -> getName() << "): ";
                for (int pin = 1; pin <= icList[i] -> getTotalPins(); ++pin) {
                    try {
                        cout << "Pin " << pin << ": " << icList[i] -> getPin(pin) << " ";
                    } catch (const exception&) {
                        cout << "N/A ";
                    }
                }
                cout << endl;
            }
        }

        else if (choice == 8) {
            cout << "Exiting program...\n";
            break;
        }

        else
            cout << "Invalid choice. Try again.\n";
    }

    // Clean up dynamically allocated memory
    for (IC* ic : icList) delete ic;
    for (Wire* wire : wireList) delete wire;

    return 0;
}
