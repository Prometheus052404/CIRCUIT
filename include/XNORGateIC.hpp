#include "IC.hpp"

template <typename T>
class XNORGateIC : public IC<T> {
    public:
        XNORGateIC();
        void simulate() override;

    private:
};
