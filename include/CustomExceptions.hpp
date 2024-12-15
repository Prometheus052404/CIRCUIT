#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include "IC.hpp"

class InvalidPinException : public exception {
    public:
        const char* what() const noexcept override {
            return "Pin access out of range.";
        }
};

#endif // CUSTOMEXCEPTIONS_HPP
