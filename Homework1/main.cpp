#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "task_flow_manager.h"

using std::cout;

void printBanner() {
    cout << R"(  _   _  ___  __  __ _______        _____  ____  _  __  _ 
 | | | |/ _ \|  \/  | ____\ \      / / _ \|  _ \| |/ / / |
 | |_| | | | | |\/| |  _|  \ \ /\ / / | | | |_) | ' /  | |
 |  _  | |_| | |  | | |___  \ V  V /| |_| |  _ <| . \  | |
 |_| |_|\___/|_|  |_|_____|  \_/\_/  \___/|_| \_\_|\_\ |_|
         https://github.com/N3agu/UPB-DSA/Homework1

)";
}

void clearScreen() {
    system("cls");
}

int runMenu(const string options[], int numOptions, const string& title) {
    int selected = 0;
    bool running = true;

    while (running) {
        clearScreen();

        printBanner();

        cout << "     " << title << "\n";

        for (int i = 0; i < numOptions; i++) {
            if (i == selected) {
                cout << "  -> " << options[i] << "\n";
            }
            else {
                cout << "     " << options[i] << "\n";
            }
        }

        int key = _getch();

        // Arrow keys send a 224 prefix
        if (key == 224) {
            key = _getch();
            
            // UP arrow
            if (key == 72) {
                selected--;
                if (selected < 0) selected = numOptions - 1;
            }
            // DOWN arrow
            else if (key == 80) {
                selected++;
                if (selected >= numOptions) selected = 0;
            }
        }
        // ENTER key 
        else if (key == 13) {
            return selected;
        }
    }
    return 0;
}

int main() {
    const int numOptions = 3;
    string mainOptions[numOptions] = {
        "Exercise 1: Interactive Task Flow Manager",
        "Exercise 2: Timeline Reconstruction System",
        "Exit Program"
    };

    bool exitProgram = false;
    while (!exitProgram) {
        int choice = runMenu(mainOptions, numOptions, "======= MAIN MENU =======");

        switch (choice) {
        case 0:
            //runExercise1();
            break;
        case 1:
            //runExercise1();
            break;
        case 2:
            cout << "\nExiting...\n";
            exitProgram = true;
            break;
        }
    }

    return 0;
}