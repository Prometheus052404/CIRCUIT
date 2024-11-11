#include "IC.h"
#include <iostream>

class NANDGateIC : public IC {
public:
    NANDGateIC();
    void simulate() override;
};
