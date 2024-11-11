#include "IC.hpp"
#include <iostream>

class XORGateIC : public IC {
public:
    XORGateIC();
    void simulate() override;
};
