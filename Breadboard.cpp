#include "Breadboard.hpp"
#include <iostream>
#include <iomanip>

Breadboard::Breadboard() : icCount(0) {

    // Initialize breadboard terminal strip as empty
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            terminalStrip[i][j] = '-';
        }
    }
    // Initialize power rails as off
    for (int i = 0; i < POWER_RAILS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            powerRails[i][j] = false;
        }
    }
    for (int i = 0; i < 10; ++i) {
        ics[i] = nullptr;
    }
}

bool Breadboard::isSpaceAvailable(int rowsNeeded, int& startRow) const {
    for (int i = 0; i <= ROWS - rowsNeeded; ++i) {
        bool spaceFree = true;
        for (int j = i; j < i + rowsNeeded; ++j) {
            if (terminalStrip[j][2] != '-' || terminalStrip[j][7] != '-') {
                spaceFree = false;
                break;
            }
        }
        if (spaceFree) {
            startRow = i;
            return true;
        }
    }
    return false;
}

bool Breadboard::insertIC(IC& ic) {
    if (icCount >= 10) {
        cerr << "Cannot place more ICs on the breadboard.\n";
        return false;
    }

    int pinCount = ic.pinCount;
    int rowsNeeded = pinCount / 2;
    int startRow;
    if (!isSpaceAvailable(rowsNeeded, startRow)) {
        cerr << "Not enough space to place the IC.\n";
        return false;
    }

    ics[icCount] = new ICPlacement{&ic, startRow};
    ++icCount;

    // Map IC pins to terminal strip
    for (int i = 0; i < rowsNeeded; ++i) {
        terminalStrip[startRow + i][2] = 'P';
        terminalStrip[startRow + i][7] = 'P';
    }

    cout << "IC placed in the ditch from rows " << startRow << " to " << (startRow + rowsNeeded - 1) << ".\n";
    return true;
}

void Breadboard::removeIC(IC& ic) {
    for (int i = 0; i < icCount; ++i) {
        if (ics[i]->ic == &ic) {
            int startRow = ics[i]->startRow;
            int rowsNeeded = ic.pinCount / 2;
            for (int j = 0; j < rowsNeeded; ++j) {
                terminalStrip[startRow + j][2] = '-';
                terminalStrip[startRow + j][7] = '-';
            }
            delete ics[i];
            ics[i] = ics[--icCount];
            ics[icCount] = nullptr;
            cout << "IC removed from the ditch.\n";
            return;
        }
    }
    cerr << "IC not found on the breadboard.\n";
}

void Breadboard::connectICPower(IC& ic) {
    bool found = false;
    for (int i = 0; i < icCount; ++i) {
        if (ics[i]->ic == &ic) {
            found = true;
            break;
        }
    }
    if (!found) {
        cerr << "IC is not on the breadboard.\n";
        return;
    }

    try {
        ic += "VCC";
        ic += "GND";
        cout << "IC connected to VCC and GND.\n";
    } catch (const runtime_error& e) {
        cerr << e.what() << "\n";
    }
}

void Breadboard::setPowerRail(int rail, bool state) {
    if (rail >= 0 && rail < POWER_RAILS) {
        for (int i = 0; i < ROWS; ++i) {
            powerRails[rail][i] = state;
        }
        cout << (rail == 1 ? "VCC" : "GND") << " rail set to " << (state ? "ON" : "OFF") << ".\n";
    } else {
        cerr << "Invalid rail number.\n";
    }
}

void Breadboard::display() const {
    cout << "Power Rails:\n";
    cout << "VCC: ";
    for (int i = 0; i < ROWS; ++i) cout << (powerRails[1][i] ? "1 " : "0 ");
    cout << "\nGND: ";
    for (int i = 0; i < ROWS; ++i) cout << (powerRails[0][i] ? "1 " : "0 ");
    cout << "\n\nTerminal Strip:\n";

    for (int i = 0; i < ROWS; ++i) {
        cout << setw(2) << i + 1 << ": ";
        for (int j = 0; j < COLUMNS; ++j) {
            cout << terminalStrip[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << "\nICs on the breadboard:\n";
    for (int i = 0; i < icCount; ++i) {
        cout << "IC " << i + 1 << " placed from rows " << ics[i]->startRow << " to " 
             << (ics[i]->startRow + ics[i]->ic->pinCount / 2 - 1) << ".\n";
    }
}
