#include "IC.hpp"

class NOTGateIC : public IC {
    public:
        NOTGateIC();
        void simulate() override;
};

