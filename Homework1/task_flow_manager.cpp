#include "task_flow_manager.h"
#include <iostream>

using namespace std;

TaskManager::TaskManager() {
    waitingNr = processedNr = undoNr = 0;
}

bool TaskManager::isIdUnique(int id) {
    Node<Task>* current = waitingTasks.pfirst;
    while (current != NULL) {
        if (current->info.id == id) return false;
        current = current->next;
    }

    current = processedTasks.pfirst;
    while (current != NULL) {
        if (current->info.id == id) return false;
        current = current->next;
    }
    return true;
}

void TaskManager::addTask(int id, const string& desc, int priority) {
    if (priority < 1 || priority > 5) {
        cout << "Error: Priority is an integer between 1 and 5.\n\n";
        return;
    }

    if (id < 0) {
        cout << "Error: Task ID must be a positive integer";
        return;
    }

    if (!isIdUnique(id)) {
        cout << "Error: Task ID must be unique.\n\n";
        return;
    }

    Task newTask = { id, desc, priority };
    waitingTasks.addLast(newTask);
    waitingNr++;

    cout << "Task added successfully:\n";
    displayTask(newTask);
}

void TaskManager::processNextTask(bool silent) {
    if (!waitingNr) {
        if (!silent) cout << "No waiting tasks available to process.\n\n";
        return;
    }

    Task task = waitingTasks.getInfo(waitingTasks.pfirst);
    waitingTasks.removeFirst();
    waitingNr--;

    processedTasks.addFirst(task);
    processedNr++;

    cout << "Processed task:\n";
    displayTask(task);
}

void TaskManager::undoLastProcessedTask() {
    if (!processedNr) {
        cout << "No processed task available for undo.\n\n";
        return;
    }

    Task task = processedTasks.getInfo(processedTasks.pfirst);
    processedTasks.removeFirst();
    processedNr--;

    waitingTasks.addFirst(task);
    waitingNr++;
    undoNr++;

    cout << "Undo successful. Task details:\n";
    displayTask(task);
}

void TaskManager::displayWaitingTasks() {
    if (waitingNr == 0) {
        cout << "No waiting tasks.\n\n";
        return;
    }

    cout << "Waiting tasks:\n";
    Node<Task>* current = waitingTasks.pfirst;
    while (current != NULL) {
        displayTask(current);
        current = current->next;
    }
    cout << "\n";
}

void TaskManager::displayProcessedHistory() {
    if (processedNr == 0) {
        cout << "No processed tasks.\n\n";
        return;
    }

    cout << "Processed task history:\n";
    Node<Task>* current = processedTasks.pfirst;
    while (current != NULL) {
        displayTask(current);
        current = current->next;
    }
    cout << "\n";
}

void TaskManager::processNextKTasks(int k) {
    if (!waitingNr) {
        cout << "No waiting tasks to process.\n\n";
        return;
    }

    cout << "Requested to process " << k << " task(s).\n\n";

    while (k > 0 && waitingNr > 0) {
        processNextTask(true);
        k--;
    }

    if (!waitingNr) {
        cout << "No more waiting tasks.\n\n";
    }
}

void TaskManager::searchTaskById(int id) {
    Node<Task>* current = waitingTasks.pfirst;
    while (current != NULL) {
        if (current->info.id == id) {
            cout << "Task found (Waiting):\n";
            displayTask(current);
            return;
        }
        current = current->next;
    }

    current = processedTasks.pfirst;
    while (current != NULL) {
        if (current->info.id == id) {
            cout << "Task found (Processed):\n";
            displayTask(current);
            return;
        }
        current = current->next;
    }

    cout << "Task not found.\n\n";
}

void TaskManager::displayStats() {
    cout << "Statistics:\n";
    cout << "Waiting tasks: " << waitingNr << "\n";
    cout << "Processed tasks: " << processedNr << "\n";
    cout << "Successful undo operations: " << undoNr << "\n\n";
}

// Can use the same method name because the parameters are different
// Also pass by reference to avoid creating a new copy of the Task struct every time displayTask is called
void TaskManager::displayTask(const Task& task) {
    cout << "ID: " << task.id << ", Description: " << task.description << ", Priority: " << task.priority << "\n\n";
}

void TaskManager::displayTask(Node<Task>* task) {
    cout << "ID: " << task->info.id << ", Description: " << task->info.description << ", Priority: " << task->info.priority << "\n";
}
