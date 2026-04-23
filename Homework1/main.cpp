#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "task_flow_manager.h"
#include "timeline_manager.h"

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

void runExercise1() {
    clearScreen();
    cout << "STORY: Interactive Task Flow Manager\n\n";
    cout << "A student team is preparing a university event.\n";
    cout << "Tasks arrive one by one and must be handled in order.\n";
    cout << "However, mistakes can happen. If a task was processed by accident,\n";
    cout << "the team wants the possibility to undo the most recently processed task.\n\n";
    cout << "Press ENTER to continue to the exercise 1 menu...";

    // ENTER key
    while (_getch() != 13) {}

    TaskManager manager;

    const int numOptions = 9;
    string menuOptions[numOptions] = {
        "1. Add new task",
        "2. Process next task",
        "3. Undo last processed task",
        "4. Display waiting tasks",
        "5. Display processed task history",
        "6. Process next k tasks",
        "7. Search task by id",
        "8. Display statistics",
        "0. Exit"
    };

    bool exitEx1 = false;
    while (!exitEx1) {
        int choice = runMenu(menuOptions, numOptions, "======= EXERCISE 1 MENU =======");
        clearScreen();

        switch (choice) {
        case 0: {
            int id, priority;
            string desc;
            cout << "Enter Task ID: ";
            cin >> id;
            cout << "Enter Description: ";
            cin >> ws;
            getline(cin, desc);
            cout << "Enter Priority (1-5): ";
            cin >> priority;
            manager.addTask(id, desc, priority);
            break;
        }
        case 1: {
            manager.processNextTask();
            break;
        }
        case 2: {
            manager.undoLastProcessedTask();
            break;
        }
        case 3: {
            manager.displayWaitingTasks();
            break;
        }
        case 4: {
            manager.displayProcessedHistory();
            break;
        }
        case 5: {
            int k;
            cout << "Enter number of tasks to process: ";
            cin >> k;
            manager.processNextKTasks(k);
            break;
        }
        case 6: {
            int id;
            cout << "Enter Task ID to search: ";
            cin >> id;
            manager.searchTaskById(id);
            break;
        }
        case 7: manager.displayStats(); break;
        case 8:
            cout << "Exiting Exercise 1...\n";
            exitEx1 = true;
            break;
        }

        if (!exitEx1) {
            cout << "Press any key to return to exercise 1 menu...";
            _getch();
        }
    }
}

int main() {
    //const int numOptions = 4;
    //string mainOptions[numOptions] = {
    //    "Exercise 1: Interactive Task Flow Manager",
    //    "Exercise 2: Timeline Reconstruction System",
    //    "Exit Program"
    //};

    //bool exitProgram = false;
    //while (!exitProgram) {
    //    int choice = runMenu(mainOptions, numOptions, "======= MAIN MENU =======");

    //    switch (choice) {
    //    case 0:
    //        runExercise1();
    //        break;
    //    case 1:
    //        //runExercise2();
    //        break;
    //    case 2:
    //        cout << "\nExiting...\n";
    //        exitProgram = true;
    //        break;
    //    }
    //}

    TimelineManager manager;

    manager.recordRecentEvent({ 1, "test1", 2332, 23 });
    manager.recordRecentEvent({ 2, "test2", 2423, 43 });
    manager.recordAncientEvent({ 0, "test3", 4354, 100 });

    manager.displayChronology();

    manager.insertEventBetween(1, 2, { 3, "test4", 1235, 95 });

    manager.displayChronology();

    manager.relocateEvent(3, 0, true);

    manager.displayChronology();

    manager.eraseCorruptedEvent(1);

    manager.displayChronology();

    int impact = manager.computeTotalImpact();
    cout << "total impact: " << impact << "\n\n";

    manager.stabilizeTimeline(80);

    manager.displayChronology();

    return 0;
}