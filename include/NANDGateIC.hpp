#include "IC.hpp"

template <typename T>
class NANDGateIC : public IC<T> {
    public:
        NANDGateIC();
        void simulate() override;
};
