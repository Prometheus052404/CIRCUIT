/* 
Project done by Team-64 (CS23I1027 - Harith Yerragolam and CS23I1064 - Parth Pandey)
This code is available on GItHub. 
Please visit the below link for the history, progress of the code and for the finished source code (in the future) of the project.
https://github.com/Prometheus052404/CIRCUIT
*/
    
#ifndef IC_HPP  // Check if IC_HPP is not defined
#define IC_HPP  // Define IC_HPP

#include <iostream>
#include <stdexcept>

using namespace std;

class IC {

    protected:
        string name;          // Name of the IC
        int* pins;            // Dynamic array to hold pin values
        int pinCount;         // Number of pins
        int vccPin;           // VCC pin number
        int groundPin;        // GND pin number
        bool powerConnected;
        bool groundConnected;

    public:
        IC(int pinCount, int vccPin, int groundPin, const string& name = "Generic IC");
        virtual ~IC();

        void connectVCC();
        void connectGround();
        void setPin(int pin, int value);
        int getPin(int pin) const;

        int& operator[](int pinNumber);
        void operator()(int pinOut, IC& otherIC, int pinIn);
        IC& operator+=(const std::string& connection);
        bool operator==(const IC& other) const;
        IC& operator!();


        virtual void simulate() = 0; // Pure virtual function for IC-specific logic
};

#endif // End of include guard for IC_HPP
