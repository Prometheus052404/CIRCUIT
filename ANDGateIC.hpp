#include "IC.hpp"
#include <iostream>

class ANDGateIC : public IC {
public:
    ANDGateIC();   // Constructor
    void simulate() override; // Override simulate method
};