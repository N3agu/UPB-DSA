#include <iostream>
#include "urban_network.h"
#include "royal_chronicle.h"

using std::cout;
using std::cin;

void printBanner() {
    cout << R"(  _   _  ___  __  __ _______        _____  ____  _  __  ____  
 | | | |/ _ \|  \/  | ____\ \      / / _ \|  _ \| |/ / |___ \ 
 | |_| | | | | |\/| |  _|  \ \ /\ / / | | | |_) | ' /    __) |
 |  _  | |_| | |  | | |___  \ V  V /| |_| |  _ <| . \   / __/ 
 |_| |_|\___/|_|  |_|_____|  \_/\_/  \___/|_| \_\_|\_\ |_____|
         https://github.com/N3agu/UPB-DSA/Homework2

)";
}

int main() {
    printBanner();

    string filenameEx1, filenameEx2;
    UrbanNetwork network;
    RoyalChronicle chronicle;

    cout << "EXERCISE 1\nEnter the name of the input file: ";
    cin >> filenameEx1;

    network.readInput(filenameEx1);
    network.solve();

    cout << "\n\nEXERCISE 2\nEnter the name of the input file: ";
    cin >> filenameEx2;

    chronicle.readInput(filenameEx2);
    chronicle.solve();

    return 0;
}