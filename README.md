# Digital Circuit Simulation Project

This project simulates a Digital Circuit System using classes representing different types of Integrated Circuits (ICs) like AND, OR, NOT, NOR, NAND, XOR, XNOR gates, and a system to connect and interact with these ICs.<br><br>The project demonstrates Object-Oriented Programming concepts in C++ (like Encapsulation, Abstraction, Operator Overloading, Inheritance, Polymorphism and Exception handling) and allows users to manipulate and simulate the behavior of various digital ICs.

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Classes and Their Functions](#classes-and-their-functions)
- [Example](#example)
- [Future Implementation](#future-implementation)
- [License](#license)

## Project Structure

The project consists of the following files:

- `IC.hpp` and `IC.cpp`: Base class `IC` for all integrated circuits.
- `ANDGateIC.hpp` and `ANDGateIC.cpp`: Class `ANDGateIC` to simulate an AND gate IC.
- `ORGateIC.hpp` and `ORGateIC.cpp`: Class `ORGateIC` to simulate an OR gate IC.
- `NOTGateIC.hpp` and `NOTGateIC.cpp`: Class `NOTGateIC` to simulate a NOT gate IC.
- `NORGateIC.hpp` and `NORGateIC.cpp`: Class `NORGateIC` to simulate a NOR gate IC.
- `NANDGateIC.hpp` and `NANDGateIC.cpp`: Class `NANDGateIC` to simulate a NAND gate IC.
- `XORateIC.hpp` and `XORGateIC.cpp`: Class `XORGateIC` to simulate a XOR gate IC.
- `NORGateIC.hpp` and `XNORGateIC.cpp`: Class `XNORGateIC` to simulate a XNOR gate IC.

## Features

- **IC Manipulation**: Set and retrieve pin values, connect ICs to each other, and use logic gates.
- **Operator Overloading**: Use operators for pin manipulation, IC comparison, and power connections.
- **Virtual Functions**: Define a `simulate()` function for IC-specific behavior and execute digital logic.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- C++ compiler supporting C++11 or later (e.g., g++)
- Basic understanding of Digital Circuits

**Note:** Now the Project can be compiled and run using just 2 commands and clear all the cache files in 1 command using MakeFile concept. <br><br>Tests will be implemented soon.

### Running the Project

Make sure you have cloned the GitHub repo into your local system if you have not already: 
```bash
git clone https://github.com/Prometheus052404/CIRCUIT.git
```

Use the below commands in `Git Bash` at your Project's Root Directory:
```bash
git fetch
git pull
```

As you have made sure that you're up-to-date, you are now ready to continue ahead!

### Make installation

**Note:** Skip this section if `make --version` gives desired output in your git bash


**If you are using Windows and have wsl installed, but not make, then follow the below steps:**
- Go to ezwinports, i.e. https://sourceforge.net/projects/ezwinports/files/
- Download `make-4.1-2-without-guile-w32-bin.zip` (get the version without guile)
- Extract zip
- Copy the contents to `C:\Program Files\Git\mingw64\` merging the folders, but do NOT overwrite/replace any exisiting files.

**If you are using Ubuntu/Debian,**
- Open WSL and update the package list:
```bash
sudo apt update
```

- Install make:
```bash
sudo apt install make
```
Navigate to your project directory within WSL and run `make`. OR
```bash
sudo apt install build-essential
```
`build-essential` includes `make` and other essential development tools like `gcc` and `g++`.

**For MacOS,** <br>
- If you have Homebrew installed, you can install `make` with:
```bash
brew install make
```

### Verify Installation
 - Open a new Git Bash window to refresh your PATH.
- Run:

```bash
make --version
```
This should display the version of `make` if it’s installed correctly.

### Implementation 
**Create the Project using Makefile:**
```bash
make
```

**Execute the code:**

```bash
./DigitalCircuitSimulator
```

**Remove all the build / cache files:**

```bash
make clean
````

**Note:** Run the above commands in git bash, at the project's root directory.


## Usage
- **Create IC objects**: Instantiate various IC objects, e.g., `ANDGateIC`, `ORGateIC`.
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


### Logic Gate ICs <br>
Each gate IC (`ANDGateIC`, `ORGateIC`, `NOTGateIC`, `NORGateIC`, `NANDGateIC`, `XORGateIC`, `XNNORGateIC`) inherits from `IC` and overrides the `simulate()` method to perform specific logic operations.

## Example
Below is a sample usage example:
```bash
#include "NANDGateIC.hpp"
#include "NORGateIC.hpp"
#include "XNORGateIC.hpp"
#include "ANDGateIC.hpp"
#include "ORGateIC.hpp"
#include "XORGateIC.hpp"
#include "NOTGateIC.hpp"

int main() 
{
    //implementing ICs
    //A MORE EXTENSIVE TEST DRIVER WILL BE PROVIDED IN THE FINAL SUBMISSION
    ANDGateIC andGateIC;

    ORGateIC orGateIC;

    NOTGateIC notGateIC;

    XORGateIC xorGateIC;

    NANDGateIC nandGateIC;

    NORGateIC norGateIC;

    XNORGateIC xnorGateIC;

    //connecting ICs
    andGateIC += "VCC";
    andGateIC += "GND";

    orGateIC += "VCC";
    orGateIC += "GND";

    notGateIC += "VCC";
    notGateIC += "GND";

    xorGateIC += "VCC";
    xorGateIC += "GND";

    nandGateIC += "VCC";
    nandGateIC += "GND";

    norGateIC += "VCC";
    norGateIC += "GND";

    xnorGateIC += "VCC";
    xnorGateIC += "GND";

    //setting pins

    andGateIC[1] = 1;
    andGateIC[2] = 1;

    cout << "AND Gate inputs: pin - 1: " << andGateIC[1] << " pin - 2: " << andGateIC[2] << endl;

    orGateIC[1] = 1;
    orGateIC[2] = 1;

    cout << "Or Gate inputs: pin - 1: " << andGateIC[1] << " pin - 2: " << andGateIC[2] << endl;

    notGateIC[1] = 1;

    cout << "NOT Gate input: pin - 1: " << notGateIC[1] << endl;

    xorGateIC[1] = 1;
    xorGateIC[2] = 1;

    cout << "XOR Gate inputs: pin - 1: " << xorGateIC[1] << " pin - 2: " << xorGateIC[2] << endl;

    nandGateIC[1] = 1;
    nandGateIC[2] = 1;

    cout << "NAND Gate inputs: pin - 1: " << nandGateIC[1] << " pin - 2: " << nandGateIC[2] << endl;

    norGateIC[1] = 1;
    norGateIC[2] = 1;

    cout << "NOR Gate inputs: pin - 1: " << norGateIC[1] << " pin - 2: " << norGateIC[2] << endl;

    xnorGateIC[1] = 1;
    xnorGateIC[2] = 1;

    cout << "XNOR Gate inputs: pin - 1: " << xnorGateIC[1] << " pin - 2: " << xnorGateIC[2] << endl;

    //simulating ICs
    andGateIC.simulate();
    orGateIC.simulate();
    notGateIC.simulate();
    xorGateIC.simulate();
    nandGateIC.simulate();
    norGateIC.simulate();
    xnorGateIC.simulate();

    //Results
    cout << "AND IC: pin - 3: " << andGateIC[3] << endl;
    cout << "OR IC: pin - 3: " << orGateIC[3] << endl;
    cout << "NOT IC: pin - 2: " << notGateIC[2] << endl;
    cout << "XOR IC: pin - 3: " << xorGateIC[3] << endl;
    cout << "NAND IC: pin - 3: " << nandGateIC[3] << endl;
    cout << "NOR IC: pin - 3: " << norGateIC[3] << endl;
    cout << "XNOR IC: pin - 3: " << xnorGateIC[3] << endl;
    
    return 0;
}
```

## Future Implementation
- In future, a `Breadboard` Class is planned to be implemetated, along with various other features, like **integrating the IC and the `Breadboard` Class**.
- Inputs shall be user given entirely.

## License
This project, **Digital Circuit Simulator**, was created by OOPS Team - 64, **Harith Yerragolam** and **Parth Pandey**.
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


