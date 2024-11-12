#include "IC.hpp"

class NORGateIC : public IC {
    public:
        NORGateIC();
        void simulate() override;
};
