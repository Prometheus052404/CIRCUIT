#include "IC.hpp"

template <typename T>
class NORGateIC : public IC<T> {
    public:
        NORGateIC();
        void simulate() override;
};
