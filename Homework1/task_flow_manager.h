#ifndef TASK_FLOW_MANAGER_H
#define TASK_FLOW_MANAGER_H

#include <string>
#include "linked_list.h"

using std::string;

struct Task {
    int id;
    string description;
    int priority;
};

class TaskManager {
    private:
        LinkedList<Task> waitingTasks;
        LinkedList<Task> processedTasks;
        int waitingNr;
        int processedNr;
        int undoNr;
        bool isIdUnique(int id);

    public:
        TaskManager();
        void addTask(int id, const std::string& desc, int priority);
        void processNextTask(bool silent = false);
        void undoLastProcessedTask();
        void displayWaitingTasks();
        void displayProcessedHistory();
        void processNextKTasks(int k);
        void searchTaskById(int id);
        void displayStats();
        void displayTask(const Task& task);
        void displayTask(Node<Task>* task);
};

#endif