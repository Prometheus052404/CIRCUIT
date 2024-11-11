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
    NANDGateIC nandGateIC;
    NORGateIC norGateIC;
    XNORGateIC xnorGateIC;
    ANDGateIC andGateIC;
    ORGateIC orGateIC;
    XORGateIC xorGateIC;
    NOTGateIC notGateIC;

    breadboard + nandGateIC;
    breadboard + norGateIC;
    breadboard + xnorGateIC;
    breadboard + andGateIC;
    breadboard + orGateIC;
    breadboard + xorGateIC;
    breadboard + notGateIC;

    breadboard.display();
    breadboard.setPowerRail(1, true);
    breadboard.setPowerRail(0, true);
    breadboard.connectICPower(nandGateIC);
    breadboard.connectICPower(norGateIC);
    breadboard.connectICPower(xnorGateIC);
    breadboard.connectICPower(andGateIC);
    breadboard.connectICPower(orGateIC);
    breadboard.connectICPower(xorGateIC);
    breadboard.connectICPower(notGateIC);

    try {
        nandGateIC.simulate();
        norGateIC.simulate();
        xnorGateIC.simulate();
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
    breadboard.removeIC(nandGateIC);
    breadboard.removeIC(norGateIC);
    breadboard.removeIC(xnorGateIC);
    breadboard.removeIC(andGateIC);
    breadboard.removeIC(orGateIC);
    breadboard.removeIC(xorGateIC);
    breadboard.removeIC(notGateIC);

    breadboard.display();
    return 0;
}
