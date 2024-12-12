#ifndef ORGATEIC_HPP
#define ORGATEIC_HPP

#include "IC.hpp"

template <typename T>
class ORGateIC : public IC<T> {
    public:
        ORGateIC();

        // ~ORGateIC() {
        //     cout << "OR Gate destructor called." << endl;
        // }

        void simulate() override;
};

#endif // ORGATEIC_HPP
