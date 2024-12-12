#ifndef ANDGATEIC_HPP
#define ANDGATEIC_HPP

#include "IC.hpp"

template <typename T>
class ANDGateIC : public IC<T> {
    public: 
        ANDGateIC();   // Constructor

        // ~ANDGateIC() {
        //     cout << "AND Gate destructor called." << endl;
        // }
        
        void simulate() override; // Override simulate method
};

#endif // ANDGATEIC_HPP
