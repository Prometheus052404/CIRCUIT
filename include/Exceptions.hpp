#include "IC.hpp"

class InvalidPinException : public exception {
public:
    const char* what() const noexcept override {
        return "Pin access out of range.";
    }
};
