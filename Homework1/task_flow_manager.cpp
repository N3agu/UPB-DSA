#include "task_flow_manager.h"
#include <iostream>

using std::cout;

TaskManager::TaskManager() {
    waitingNr = processedNr = undoNr = 0;
}

bool TaskManager::isIdUnique(int id) {
    bool unique = true;

    for (int i = 0; i < waitingNr; i++) {
        Task t = waitingTasks.dequeue();
        if (t.id == id) unique = false;
        waitingTasks.enqueue(t);
    }

    Source_Stack<Task> tempStack;
    while (!processedTasks.isEmpty()) {
        Task t = processedTasks.pop();
        if (t.id == id) unique = false;
        tempStack.push(t);
    }

    while (!tempStack.isEmpty()) {
        processedTasks.push(tempStack.pop());
    }

    return unique;
}

void TaskManager::addTask(int id, const string& desc, int priority) {
    if (priority < 1 || priority > 5) {
        cout << "Error: Priority is an integer between 1 and 5.\n\n";
        return;
    }

    if (id < 0) {
        cout << "Error: Task ID must be a positive integer.\n\n";
        return;
    }

    if (!isIdUnique(id)) {
        cout << "Error: Task ID must be unique.\n\n";
        return;
    }

    Task newTask = { id, desc, priority };
    waitingTasks.enqueue(newTask);
    waitingNr++;

    cout << "Task added successfully:\n";
    displayTask(newTask);
    cout << "\n";
}

void TaskManager::processNextTask(bool silent) {
    if (waitingNr == 0) {
        if (!silent) cout << "No waiting tasks available to process.\n\n";
        return;
    }

    Task task = waitingTasks.dequeue();
    waitingNr--;

    processedTasks.push(task);
    processedNr++;

    cout << "Processed task:\n";
    displayTask(task);
    cout << "\n";
}

void TaskManager::undoLastProcessedTask() {
    if (processedNr == 0) {
        cout << "No processed task available for undo.\n\n";
        return;
    }

    Task task = processedTasks.pop();
    processedNr--;

    waitingTasks.enqueue(task);

    for (int i = 0; i < waitingNr; i++) {
        waitingTasks.enqueue(waitingTasks.dequeue());
    }

    waitingNr++;
    undoNr++;

    cout << "Undo successful. Restored task:\n";
    displayTask(task);
    cout << "\n";
}

void TaskManager::displayWaitingTasks() {
    if (waitingNr == 0) {
        cout << "No waiting tasks.\n\n";
        return;
    }

    cout << "Waiting tasks:\n";
    for (int i = 0; i < waitingNr; i++) {
        Task t = waitingTasks.dequeue();
        displayTask(t);
        waitingTasks.enqueue(t);
    }
    cout << "\n";
}

void TaskManager::displayProcessedHistory() {
    if (processedNr == 0) {
        cout << "No processed tasks.\n\n";
        return;
    }

    cout << "Processed task history:\n";
    Source_Stack<Task> tempStack;

    while (!processedTasks.isEmpty()) {
        Task t = processedTasks.pop();
        displayTask(t);
        tempStack.push(t);
    }

    while (!tempStack.isEmpty()) {
        processedTasks.push(tempStack.pop());
    }
    cout << "\n";
}

void TaskManager::processNextKTasks(int k) {
    if (waitingNr == 0) {
        cout << "No waiting tasks to process.\n\n";
        return;
    }

    cout << "Requested to process " << k << " tasks.\n\n";

    while (k > 0 && waitingNr > 0) {
        processNextTask(true);
        k--;
    }

    if (waitingNr == 0) {
        cout << "No more waiting tasks.\n\n";
    }
}

void TaskManager::searchTaskById(int id) {
    bool found = false;

    for (int i = 0; i < waitingNr; i++) {
        Task t = waitingTasks.dequeue();
        if (t.id == id && !found) {
            cout << "Task found (Waiting):\n";
            displayTask(t);
            cout << "\n";
            found = true;
        }
        waitingTasks.enqueue(t);
    }

    if (found) return;

    Source_Stack<Task> tempStack;
    while (!processedTasks.isEmpty()) {
        Task t = processedTasks.pop();
        if (t.id == id && !found) {
            cout << "Task found (Processed):\n";
            displayTask(t);
            cout << "\n";
            found = true;
        }
        tempStack.push(t);
    }

    while (!tempStack.isEmpty()) {
        processedTasks.push(tempStack.pop());
    }

    if (!found) {
        cout << "Task not found.\n\n";
    }
}

void TaskManager::displayStats() {
    cout << "Statistics:\n";
    cout << "Waiting tasks: " << waitingNr << "\n";
    cout << "Processed tasks: " << processedNr << "\n";
    cout << "Successful undo operations: " << undoNr << "\n\n";
}

// Also pass by reference to avoid creating a new copy of the Task struct every time displayTask is called
void TaskManager::displayTask(const Task& task) {
    cout << "ID: " << task.id << ", Description: " << task.description << ", Priority: " << task.priority << "\n";
}