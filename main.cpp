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
        cout << "\n--- Circuit Simulator Menu ---\n";
        cout << "1. Create a new IC\n";
        cout << "2. Set pin values\n";
        cout << "3. Connect ICs with a wire\n";
        cout << "4. Simulate IC\n";
        cout << "5. View IC pin states\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
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

            if (powerChoice == "y") {
                newIC->connectVCC();
                newIC->connectGround();
                cout << "Power connected to IC.\n";
            }

            icList.push_back(newIC);
            cout << "IC created and added to the circuit.\n";
        }

        else if (choice == 2) {
            if (icList.empty()) {
                cout << "No ICs available. Create an IC first.\n";
                continue;
            }

            size_t icIndex;
            int pin, value;
            cout << "Select IC index (1-" << icList.size() << "): ";
            cin >> icIndex;
            if (icIndex < 1 || icIndex > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            IC* selectedIC = icList[icIndex - 1];
            cout << "Enter pin number to set (1-" << selectedIC->getTotalPins() << "): ";
            cin >> pin;
            cout << "Enter value for pin " << pin << " (0/1): ";
            cin >> value;

            try {
                selectedIC->setPin(pin, value);
                cout << "Pin value set successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 3) {
            if (icList.size() < 2) {
                cout << "At least two ICs are required for connection.\n";
                continue;
            }

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

            if (srcIC < 1 || srcIC > icList.size() || destIC < 1 || destIC > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            try {
                Wire* newWire = new Wire(icList[srcIC - 1], srcPin, icList[destIC - 1], destPin);
                newWire->connect();
                wireList.push_back(newWire);
                cout << "Wire connected successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 4) {
            if (icList.empty()) {
                cout << "No ICs available to simulate.\n";
                continue;
            }

            size_t icIndex;
            cout << "Select IC index to simulate (1-" << icList.size() << "): ";
            cin >> icIndex;
            if (icIndex < 1 || icIndex > icList.size()) {
                cout << "Invalid IC index.\n";
                continue;
            }

            try {
                icList[icIndex - 1]->simulate();
                cout << "IC simulation completed successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 5) {
            if (icList.empty()) {
                cout << "No ICs available to view.\n";
                continue;
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
        }

        else if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    // Clean up dynamically allocated memory
    for (IC* ic : icList) delete ic;
    for (Wire* wire : wireList) delete wire;

    return 0;
}
