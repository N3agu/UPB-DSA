#include <iostream>
#include "task_flow_manager.h"

using std::cout;

int main() {
	cout << "Homework 1";
    TaskManager manager;

    manager.addTask(101, "1", 3);
    manager.addTask(102, "2", 5);
    manager.addTask(103, "3", 2);

    manager.addTask(104, "test1", 6);
    manager.addTask(101, "test2", 4);

    manager.displayWaitingTasks();

    manager.processNextTask();
    manager.processNextTask();

    manager.displayProcessedHistory();

    manager.undoLastProcessedTask();

    manager.displayWaitingTasks();
    manager.displayProcessedHistory();

    manager.searchTaskById(101);
    manager.searchTaskById(102);
    manager.searchTaskById(999);

    manager.displayStats();
}