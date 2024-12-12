#ifndef NORGATEIC_HPP
#define NORGATEIC_HPP

#include "IC.hpp"

template <typename T>
class NORGateIC : public IC<T> {
    public:
        NORGateIC();

        // ~NORGateIC() {
        //     cout << "NOR Gate destructor called." << endl;
        // }

        void simulate() override;
};

#endif // NORGATEIC_HPP
