#include "IC.h"
#include <iostream>

class NORGateIC : public IC {
public:
    NORGateIC();
    void simulate() override;
};
