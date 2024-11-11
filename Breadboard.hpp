#ifndef BREADBOARD_H
#define BREADBOARD_H

#include "IC.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Breadboard {
private:
    static const int ROWS = 30;       // Number of rows in the terminal strip
    static const int COLUMNS = 10;    // Columns A-J in each row
    static const int POWER_RAILS = 2; // Two power rails: VCC and GND
    char terminalStrip[ROWS][COLUMNS]; // Grid for placing components
    bool powerRails[POWER_RAILS][ROWS]; // Power rails for VCC and GND
    struct ICPlacement {
        IC* ic;
        int startRow;
    };
    ICPlacement* ics[10];  // Assume a maximum of 10 ICs can be placed
    int icCount;

    bool isSpaceAvailable(int rowsNeeded, int& startRow) const; // Helper to find space

public:
    Breadboard();                // Constructor
    bool insertIC(IC& ic);       // Insert an IC in the ditch (center gap)
    void removeIC(IC& ic);       // Remove a specific IC
    void connectICPower(IC& ic); // Connect VCC and GND to a specific IC
    void setPowerRail(int rail, bool state); // Turn power rails ON or OFF
    void display() const;        // Display breadboard layout
};

#endif
