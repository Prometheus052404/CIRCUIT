#include "IC.hpp"

class NANDGateIC : public IC {
    public:
        NANDGateIC();
        void simulate() override;
};
