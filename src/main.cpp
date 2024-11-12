/* 
Project done by Team-64 (CS23I1027 - Harith Yerragolam and CS23I1064 - Parth Pandey)
https://github.com/Prometheus052404/CIRCUIT
*/

#include "../include/NANDGateIC.hpp"
#include "../include/NORGateIC.hpp"
#include "../include/XNORGateIC.hpp"
#include "../include/ANDGateIC.hpp"
#include "../include/ORGateIC.hpp"
#include "../include/XORGateIC.hpp"
#include "../include/NOTGateIC.hpp"

int main() 
{
    //implementing ICs
    //A MORE EXTENSIVE TEST DRIVER WILL BE PROVIDED IN THE FINAL SUBMISSION
    ANDGateIC andGateIC;

    ORGateIC orGateIC;

    NOTGateIC notGateIC;

    XORGateIC xorGateIC;

    NANDGateIC nandGateIC;

    NORGateIC norGateIC;

    XNORGateIC xnorGateIC;

    //connecting ICs
    andGateIC += "VCC";
    andGateIC += "GND";

    orGateIC += "VCC";
    orGateIC += "GND";

    notGateIC += "VCC";
    notGateIC += "GND";

    xorGateIC += "VCC";
    xorGateIC += "GND";

    nandGateIC += "VCC";
    nandGateIC += "GND";

    norGateIC += "VCC";
    norGateIC += "GND";

    xnorGateIC += "VCC";
    xnorGateIC += "GND";

    //setting pins

    andGateIC[1] = 1;
    andGateIC[2] = 1;

    cout << "AND Gate inputs: pin - 1: " << andGateIC[1] << " pin - 2: " << andGateIC[2] << endl;

    orGateIC[1] = 1;
    orGateIC[2] = 1;

    cout << "Or Gate inputs: pin - 1: " << andGateIC[1] << " pin - 2: " << andGateIC[2] << endl;

    notGateIC[1] = 1;

    cout << "NOT Gate input: pin - 1: " << notGateIC[1] << endl;

    xorGateIC[1] = 1;
    xorGateIC[2] = 1;

    cout << "XOR Gate inputs: pin - 1: " << xorGateIC[1] << " pin - 2: " << xorGateIC[2] << endl;

    nandGateIC[1] = 1;
    nandGateIC[2] = 1;

    cout << "NAND Gate inputs: pin - 1: " << nandGateIC[1] << " pin - 2: " << nandGateIC[2] << endl;

    norGateIC[1] = 1;
    norGateIC[2] = 1;

    cout << "NOR Gate inputs: pin - 1: " << norGateIC[1] << " pin - 2: " << norGateIC[2] << endl;

    xnorGateIC[1] = 1;
    xnorGateIC[2] = 1;

    cout << "XNOR Gate inputs: pin - 1: " << xnorGateIC[1] << " pin - 2: " << xnorGateIC[2] << endl;

    //simulating ICs
    andGateIC.simulate();
    orGateIC.simulate();
    notGateIC.simulate();
    xorGateIC.simulate();
    nandGateIC.simulate();
    norGateIC.simulate();
    xnorGateIC.simulate();

    //Results
    cout << "AND IC: pin - 3: " << andGateIC[3] << endl;
    cout << "OR IC: pin - 3: " << orGateIC[3] << endl;
    cout << "NOT IC: pin - 2: " << notGateIC[2] << endl;
    cout << "XOR IC: pin - 3: " << xorGateIC[3] << endl;
    cout << "NAND IC: pin - 3: " << nandGateIC[3] << endl;
    cout << "NOR IC: pin - 3: " << norGateIC[3] << endl;
    cout << "XNOR IC: pin - 3: " << xnorGateIC[3] << endl;
    
    return 0;
}
