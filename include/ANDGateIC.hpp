#include "IC.hpp"

template <typename T>
class ANDGateIC : public IC<T> {
    public: ANDGateIC();   // Constructor
    public: void simulate() override; // Override simulate method
};
