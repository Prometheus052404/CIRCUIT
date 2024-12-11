#ifndef NANDGATEIC_HPP
#define NANDGATEIC_HPP

#include "IC.hpp"

template <typename T>
class NANDGateIC : public IC<T> {
    public:
        NANDGateIC();
        void simulate() override;
};

#endif // NANDGATEIC_HPP
