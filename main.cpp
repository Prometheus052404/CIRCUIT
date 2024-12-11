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
#include <memory>
#include <vector>
#include <iostream>

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
    } 
    
    else
        cout << "Invalid pin number!" << endl;
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
    
    else
        cout << "Invalid pin connection!" << endl;
}

int main() {
    vector<IC*> icList;
    vector<Wire*> wireList;

    while (true) {
        // Menu display
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

        // User input
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
                cout << i + 1 << ". " << icList[i]->getName() << endl;
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
                newIC->connectVCC();
                newIC->connectGround();
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
                cout << i + 1 << ". " << icList[i]->getName() << endl;

            cout << "-----------------------------------\n";
            cout << "Select IC index (1-" << icList.size() << "): ";
            cin >> icIndex;

            if (!validateInput(icIndex, size_t(1), icList.size())) {
                cout << "Invalid IC index.\n";
                continue;
            }

            IC* selectedIC = icList[icIndex - 1];
            cout << "Enter pin number to set (1-" << selectedIC->getTotalPins() << "): ";
            cin >> pin;
            cout << "Enter value for pin " << pin << " (0/1): ";
            cin >> value;

            setPinValue(*selectedIC, pin, value);
        } 
        
        else if (choice == 4) {
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

            if (!validateInput(srcIC, size_t(1), icList.size()) ||
                !validateInput(destIC, size_t(1), icList.size())) {
                cout << "Invalid IC index.\n";
                continue;
            }

            connectICs(*icList[srcIC - 1], srcPin, *icList[destIC - 1], destPin);
        } 
        
        else if (choice == 8) {
            cout << "Exiting program...\n";
            break;
        } 
        
        else
            cout << "Invalid choice. Try again.\n";
    }

    // Cleanup
    for (IC* ic : icList) delete ic;
    for (Wire* wire : wireList) delete wire;

    return 0;
}
