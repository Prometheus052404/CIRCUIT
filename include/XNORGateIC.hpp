#ifndef XNORGATEIC_HPP
#define XNORGATEIC_HPP

#include "IC.hpp"

template <typename T>
class XNORGateIC : public IC<T> {
    public:
        XNORGateIC();
        void simulate() override;
};

#endif // XNORGATEIC_HPP
