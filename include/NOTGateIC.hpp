#ifndef NOTGATEIC_HPP
#define NOTGATEIC_HPP

#include "IC.hpp"

template <typename T>
class NOTGateIC : public IC<T> {
    public:
        NOTGateIC();

        // ~NOTGateIC() {
        //     cout << "NOT Gate destructor called." << endl;
        // }
        
        void simulate() override;
};

#endif // NOTGATEIC_HPP
