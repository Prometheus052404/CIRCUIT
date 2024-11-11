#include "IC.hpp"
#include <iostream>

class ORGateIC : public IC {
public:
    ORGateIC();
    void simulate() override;
};

