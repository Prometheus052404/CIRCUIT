#include "IC.hpp"

class ANDGateIC : public IC {
public:
    ANDGateIC();   // Constructor
    void simulate() override; // Override simulate method
};
