#include <iostream>
#include "urban_network.h"

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

    string filename;
    cout << "Enter the name of the input file: ";
    cin >> filename;

    UrbanNetwork network;
    network.readInput(filename);
    network.solve();

    return 0;
}