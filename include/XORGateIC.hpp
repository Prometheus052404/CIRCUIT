#ifndef XORGATEIC_HPP
#define XORGATEIC_HPP

#include "IC.hpp"

template <typename T>
class XORGateIC : public IC<T> {
    public:
        XORGateIC();
        void simulate() override;
};

#endif // XORGATEIC_HPP
