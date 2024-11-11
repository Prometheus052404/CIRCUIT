#include "breadboard.hpp"
#include "NANDGateIC.hpp"
#include "NORGateIC.hpp"
#include "XNORGateIC.hpp"
#include "ANDGateIC.hpp"
#include "ORGateIC.hpp"
#include "XORGateIC.hpp"
#include "NOTGateIC.hpp"

int main() {
    Breadboard breadboard;
    
    ANDGateIC andGateIC;
    ORGateIC orGateIC;
    XORGateIC xorGateIC;
    NOTGateIC notGateIC;

    breadboard + andGateIC;
    breadboard + orGateIC;
    breadboard + xorGateIC;
    breadboard + notGateIC;

    breadboard.display();
    breadboard.setPowerRail(1, true);
    breadboard.setPowerRail(0, true);
    breadboard.connectICPower(andGateIC);
    breadboard.connectICPower(orGateIC);
    breadboard.connectICPower(xorGateIC);
    breadboard.connectICPower(notGateIC);

    andGateIC[1] = 1;
    andGateIC[2] = 1;
    orGateIC[1] = 1;
    orGateIC[2] = 0;
    xorGateIC[1] = 1;
    xorGateIC[2] = 0;
    notGateIC[1] = 1;
    

    try {
        andGateIC.simulate();
        orGateIC.simulate();
        xorGateIC.simulate();
        notGateIC.simulate();
    } catch (const runtime_error& e) {
        cerr << e.what() << "\n";
    }

    breadboard.display();
    breadboard.setPowerRail(1, false);
    breadboard.setPowerRail(0, false);
    breadboard.removeIC(andGateIC);
    breadboard.removeIC(orGateIC);
    breadboard.removeIC(xorGateIC);
    breadboard.removeIC(notGateIC);

    breadboard.display();
    return 0;
}
