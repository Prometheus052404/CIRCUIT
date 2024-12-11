#ifndef NOTGATEIC_HPP
#define NOTGATEIC_HPP

#include "IC.hpp"

template <typename T>
class NOTGateIC : public IC<T> {
    public:
        NOTGateIC();
        void simulate() override;
};

#endif // NOTGATEIC_HPP
