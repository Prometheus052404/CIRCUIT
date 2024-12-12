#ifndef XORGATEIC_HPP
#define XORGATEIC_HPP

#include "IC.hpp"

template <typename T>
class XORGateIC : public IC<T> {
    public:
        XORGateIC();

        // ~XORGateIC() {
        //     cout << "XOR Gate destructor called." << endl;
        // }

        void simulate() override;
};

#endif // XORGATEIC_HPP
