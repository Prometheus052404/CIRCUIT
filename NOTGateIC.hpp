#include "IC.hpp"
#include <iostream>

class NOTGateIC : public IC {
public:
    NOTGateIC();
    void simulate() override;
};

