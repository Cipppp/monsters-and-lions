#include <iostream>

#include "./data/model/Siren.h"
#include "./data/model/Vampire.h"
#include "./utils.h"

using namespace std;

int main() {
    // Create a vampire class
    Vampire vampire;

    // show the makeup price of vampire
    vampire.showMakeupPricePerDay();

    // Create a sirens class
    Siren siren;

    // show the makeup price of siren
    siren.showMakeupPricePerDay();

    return 0;
}
