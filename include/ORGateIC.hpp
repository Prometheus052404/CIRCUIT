#include "IC.hpp"

template <typename T>
class ORGateIC : public IC<T> {
    public:
        ORGateIC();
        void simulate() override;
};

