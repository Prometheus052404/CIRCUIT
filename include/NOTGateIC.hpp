#include "IC.hpp"

template <typename T>
class NOTGateIC : public IC<T> {
    public:
        NOTGateIC();
        void simulate() override;
};

