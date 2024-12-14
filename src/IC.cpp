#include "../include/IC.hpp"

/**
 * @brief Constructor for the IC class.
 * 
 * This constructor initializes an IC with the specified number of pins, VCC pin, GND pin, and a name.
 * It also initializes the pins to default values of type T.
 * 
 * @tparam T Data type of the pin values (e.g., int, float, bool).
 * @param pinCount Total number of pins on the IC.
 * @param vccPin Pin number where VCC is connected.
 * @param groundPin Pin number where GND is connected.
 * @param name Name or identifier for the IC.
 */
template <typename T>
IC<T> :: IC(int pinCount, int vccPin, int groundPin, const string& name)
    : name(name), pins(pinCount, T()), pinCount(pinCount), vccPin(vccPin), groundPin(groundPin), powerConnected(false), groundConnected(false) {}

/**
 * @brief Gets the total number of pins on the IC.
 * 
 * @tparam T Data type of the pin values.
 * @return int The total number of pins on the IC.
 */
template <typename T>
int IC<T> :: getTotalPins() const {
        return pinCount;
    }

/**
 * @brief Connects the VCC pin of the IC.
 * 
 * This function sets the VCC pin to a high state (1) and marks it as connected.
 * 
 * @tparam T Data type of the pin values.
 * @throws runtime_error If VCC is already connected.
 */
template <typename T>
void IC<T> :: connectVCC() {
    if (powerConnected)
        throw runtime_error("VCC already connected.");

    pins[vccPin - 1] = T(1);
    powerConnected = true;
}

/**
 * @brief Connects the GND (ground) pin of the IC.
 * 
 * This function sets the GND pin to a low state (0) and marks it as connected.
 * 
 * @tparam T Data type of the pin values.
 * @throws runtime_error If VCC is not connected before connecting GND.
 */
template <typename T>
void IC<T> :: connectGround() {
    if (!powerConnected) 
        throw runtime_error("Connect VCC before connecting GND.");

    pins[groundPin - 1] = T(0);
    groundConnected = true;
}

/**
 * @brief Sets the value of a specific pin on the IC.
 * 
 * @tparam T Data type of the pin values.
 * @param pin The pin number to be set (1-indexed).
 * @param value The value to be assigned to the pin.
 * @throws out_of_range If the pin number is invalid.
 */
template <typename T>
void IC<T> :: setPin(int pin, T value) {
    if ((pin >= 1) && (pin <= pinCount))
        pins[pin - 1] = value;
    else
        throw out_of_range("Invalid pin number");
}

/**
 * @brief Gets the value of a specific pin on the IC.
 * 
 * @tparam T Data type of the pin values.
 * @param pin The pin number to get the value from (1-indexed).
 * @return T The value of the pin.
 * @throws out_of_range If the pin number is invalid.
 */
template <typename T>
T IC<T> :: getPin(int pin) const {
    if ((pin >= 1) && (pin <= pinCount))
        return pins[pin - 1];
    else
        throw out_of_range("Invalid pin number");
}

/**
 * @brief Operator overload to access a pin using the [] operator.
 * 
 * @tparam T Data type of the pin values.
 * @param pinNumber The 0-indexed pin number.
 * @return T The value of the pin.
 * @throws out_of_range If the pin number is invalid.
 */
template <typename T>
T IC<T> :: operator[](int pinNumber) {
    if ((pinNumber >= 0) && (pinNumber < pinCount))
        return pins[pinNumber-1];
    else
        throw out_of_range("Invalid pin number");
}

/**
 * @brief Operator overload to connect an output pin to another IC's input pin.
 * 
 * @tparam T Data type of the pin values.
 * @param pinOut The output pin on the current IC.
 * @param otherIC Reference to the other IC to connect to.
 * @param pinIn The input pin on the other IC.
 * @throws out_of_range If the pin numbers are invalid.
 */
template <typename T>
void IC<T> :: operator()(int pinOut, IC<T>& otherIC, int pinIn) {
    if (pinOut < 1 || pinOut > pinCount || pinIn < 1 || pinIn > otherIC.getTotalPins())
            throw out_of_range("Invalid pin connection");
        otherIC.setPin(pinIn, getPin(pinOut));
    }

/**
 * @brief Operator overload to connect the IC to VCC or GND using the += operator.
 * 
 * @tparam T Data type of the pin values.
 * @param connection The type of connection ("VCC" or "GND").
 * @return IC<T>& Reference to the current IC.
 */
template <typename T>
IC<T>& IC<T> :: operator += (const string& connection) {
    if (connection == "VCC")
        connectVCC();
    else if (connection == "GND")
        connectGround();

    return *this;
}

/**
 * @brief Operator overload to compare two ICs for equality.
 * 
 * @tparam T Data type of the pin values.
 * @param other The other IC to compare with.
 * @return true If both ICs have the same pin count and pin values.
 * @return false Otherwise.
 */
template <typename T>
bool IC<T> :: operator == (const IC<T>& other) const {
    if (pinCount != other.pinCount) 
        return false;

    for (int i = 0; i < pinCount; i++) 
        if (pins[i] != other.pins[i]) 
            return false;

    return true;
}

/**
 * @brief Operator overload to reset all pin values to 0 using the ! operator.
 * 
 * @tparam T Data type of the pin values.
 * @return IC<T>& Reference to the current IC.
 */
template <typename T>
IC<T>& IC<T> :: operator!() {
    for (int i = 0; i < pinCount; i++)
        pins[i] = T(0);

    return *this;
}

// Explicit instantiations
template class IC<int>;
template class IC<float>;
template class IC<bool>;