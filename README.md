# Digital Circuit Simulation Project

This project simulates a Digital Circuit System using classes representing different types of Integrated Circuits (ICs) like AND, OR, NOT, NOR, NAND, XOR, XNOR gates, as well as a Breadboard to connect and interact with these ICs.<br><br>The project demonstrates Object-Oriented Programming concepts in C++ (like Encapsulation, Abstraction, Operator Overloading, Inheritance, Polymorphism, Exception handling and Templates) and allows users to manipulate and simulate the behavior of various digital ICs.

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Classes and Their Functions](#classes-and-their-functions)
- [Example](#example)
- [License](#license)

## Project Structure

The project consists of the following files:

- `IC.hpp` and `IC.cpp`: Base class `IC` for all integrated circuits.
- `Breadboard.hpp` and `Breadboard.cpp`: Class `Breadboard` to manage ICs and simulate connections.
- `ANDGateIC.hpp` and `ANDGateIC.cpp`: Class `ANDGateIC` to simulate an AND gate IC.
- `ORGateIC.hpp` and `ORGateIC.cpp`: Class `ORGateIC` to simulate an OR gate IC.
- `NOTGateIC.hpp` and `NOTGateIC.cpp`: Class `NOTGateIC` to simulate a NOT gate IC.
- `NORGateIC.hpp` and `NORGateIC.cpp`: Class `NORGateIC` to simulate a NOR gate IC.
- `NANDGateIC.hpp` and `NANDGateIC.cpp`: Class `NANDGateIC` to simulate a NAND gate IC.
- `XORateIC.hpp` and `XORGateIC.cpp`: Class `XORGateIC` to simulate a XOR gate IC.
- `NORGateIC.hpp` and `XNORGateIC.cpp`: Class `XNORGateIC` to simulate a XNOR gate IC.

## Features

- **Breadboard Simulation**: Create a virtual breadboard, insert ICs, and connect power rails.
- **IC Manipulation**: Set and retrieve pin values, connect ICs to each other, and use logic gates.
- **Operator Overloading**: Use operators for pin manipulation, IC comparison, and power connections.
- **Virtual Functions**: Define a `simulate()` function for IC-specific behavior and execute digital logic.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- C++ compiler supporting C++11 or later (e.g., g++)
- Basic understanding of Digital Circuits

### Compiling the Project

Use the following command to compile:

```bash
g++ -o DigitalCircuitSimulator main.cpp IC.cpp Breadboard.cpp ANDGateIC.cpp ORGateIC.cpp NOTGateIC.cpp NORGateIC.cpp NANDGateIC.cpp XORGateIC.cpp XNORGateIC.cpp
```

### Running the Project

Use the following command to run:

```bash
./DigitalCircuitSimulator
```

## Usage
- **Create IC objects**: Instantiate various IC objects, e.g., `ANDGateIC`, `ORGateIC`.
- **Insert ICs on the Breadboard**: Use the `Breadboard` class to add ICs and manage their placement.
- **Connect Power**: Connect VCC and GND to the ICs to simulate power supply.
- **Simulate**: Call the `simulate()` function on each IC to execute its digital logic.

## Classes and Their Functions
### Class `IC`
The base class for all ICs.

- **Constructor**: Initializes pins, VCC, and GND.
- **connectVCC()**: Connects the IC to the power rail.
- **connectGround()**: Connects the IC to the ground rail.
- **setPin(int pin, int value)**: Sets a pin's value.
- **getPin(int pin)**: Gets a pin's value.
- **simulate()**: Pure virtual function for IC-specific logic.

### Class `Breadboard`
Represents a breadboard for placing ICs.

- **insertIC(IC& ic)**: Places an IC on the breadboard.
- **connectICPower(IC& ic)**: Connects VCC and GND to an IC.
- **display()**: Displays the breadboard layout.

### Logic Gate ICs <br>
Each gate IC (`ANDGateIC`, `ORGateIC`, `NOTGateIC`, `NORGateIC`, `NANDGateIC`, `XORGateIC`, `XNNORGateIC`) inherits from `IC` and overrides the `simulate()` method to perform specific logic operations.

## Example
Below is a sample usage example:
```bash
#include "Breadboard.hpp"
#include "ANDGateIC.hpp"
#include "ORGateIC.hpp"

int main() {
    Breadboard breadboard;
    ANDGateIC andIC;
    ORGateIC orIC;

    breadboard.insertIC(andIC);
    breadboard.insertIC(orIC);
    breadboard.connectICPower(andIC);
    breadboard.connectICPower(orIC);

    andIC.setPin(1, 1);
    andIC.setPin(2, 0);
    andIC.simulate();
    cout << "AND Gate Output (Pin 3): " << andIC.getPin(3) << endl;

    return 0;
}
```

## License
This project, **Digital Circuit Simulator**, was created by **Harith Yerragolam** and **Parth Pandey**.
<br><br>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, subject to the following conditions:
<br>
<ul style="list-style-type:none;">
  <li>The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.</li>
</ul>
<br>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.


