#include "IC.h"
#include <iostream>

class XORGateIC : public IC {
public:
    XORGateIC();
    void simulate() override;
};
