#include "IC.hpp"

template <typename T>
class XORGateIC : public IC<T> {
    public:
        XORGateIC();
        void simulate() override;
};
