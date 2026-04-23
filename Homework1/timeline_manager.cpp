#include "timeline_manager.h"
#include <iostream>

using std::cout;

TimelineManager::TimelineManager() {}

Node<Event>* TimelineManager::findEventNode(int id) {
    Node<Event>* curr = timeline.pfirst;
    while (curr != NULL) {
        if (curr->info.id == id) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void TimelineManager::removeEventNode(Node<Event>* node) {
    if (node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node == timeline.pfirst) {
        timeline.pfirst = node->next;
    }
    if (node == timeline.plast) {
        timeline.plast = node->prev;
    }

    delete node;
}

void TimelineManager::recordAncientEvent(Event e) {
    timeline.addFirst(e);
}

void TimelineManager::recordRecentEvent(Event e) {
    timeline.addLast(e);
}

void TimelineManager::insertEventBetween(int leftId, int rightId, Event e) {
    Node<Event>* leftNode = findEventNode(leftId);

    if (leftNode == NULL || leftNode->next == NULL || leftNode->next->info.id != rightId) {
        cout << "Error: Events " << leftId << " and " << rightId << " are do not exist or are not consecutive.\n\n";
        return;
    }

    Node<Event>* newNode = new Node<Event>;
    newNode->info = e;
    newNode->prev = leftNode;
    newNode->next = leftNode->next;

    leftNode->next->prev = newNode;
    leftNode->next = newNode;

    cout << "Event " << e.id << " was inserted between " << leftId << " and " << rightId << ".\n\n";
}

void TimelineManager::eraseCorruptedEvent(int id) {
    Node<Event>* target = findEventNode(id);
    if (target == NULL) {
        cout << "Error: Event " << id << " was not found.\n\n";
        return;
    }

    removeEventNode(target);
    cout << "Corrupted event " << id << " was successfully erased.\n\n";
}

void TimelineManager::relocateEvent(int idToMove, int newNeighborId, bool before) {
    if (idToMove == newNeighborId) return;

    Node<Event>* nodeToMove = findEventNode(idToMove);
    Node<Event>* neighbor = findEventNode(newNeighborId);

    if (nodeToMove == NULL || neighbor == NULL) {
        cout << "Error: One or both events couldn't be found for relocation.\n\n";
        return;
    }

    Event e = nodeToMove->info;
    removeEventNode(nodeToMove);

    Node<Event>* newNode = new Node<Event>;
    newNode->info = e;

    if (before) {
        newNode->next = neighbor;
        newNode->prev = neighbor->prev;
        if (neighbor->prev != NULL) {
            neighbor->prev->next = newNode;
        }
        neighbor->prev = newNode;

        if (timeline.pfirst == neighbor) {
            timeline.pfirst = newNode;
        }
    }
    else {
        newNode->prev = neighbor;
        newNode->next = neighbor->next;
        if (neighbor->next != NULL) {
            neighbor->next->prev = newNode;
        }
        neighbor->next = newNode;

        if (timeline.plast == neighbor) {
            timeline.plast = newNode;
        }
    }

    cout << "Event " << idToMove << " was relocated.\n\n";
}

void TimelineManager::displayChronology() {
    cout << "Current Timeline Chronology:\n";
    Node<Event>* curr = timeline.pfirst;

    if (curr == NULL) {
        cout << "The timeline is currently empty.\n\n";
        return;
    }

    while (curr != NULL) {
        cout << "[" << curr->info.year << "] " << curr->info.description << " (ID: " << curr->info.id << ", Impact: " << curr->info.impact << ")\n";
        curr = curr->next;
    }
    cout << "\n";
}

int TimelineManager::computeTotalImpact() {
    int total = 0;
    Node<Event>* curr = timeline.pfirst;
    while (curr != NULL) {
        total += curr->info.impact;
        curr = curr->next;
    }
    return total;
}

void TimelineManager::stabilizeTimeline(int threshold) {
    LinkedList<Event> highImpact;
    LinkedList<Event> lowImpact;

    Node<Event>* curr = timeline.pfirst;
    while (curr != NULL) {
        if (curr->info.impact >= threshold) {
            highImpact.addLast(curr->info);
        }
        else {
            lowImpact.addLast(curr->info);
        }
        curr = curr->next;
    }

    while (!timeline.isEmpty()) {
        timeline.removeFirst();
    }

    curr = highImpact.pfirst;
    while (curr != NULL) {
        timeline.addLast(curr->info);
        curr = curr->next;
    }

    curr = lowImpact.pfirst;
    while (curr != NULL) {
        timeline.addLast(curr->info);
        curr = curr->next;
    }

    cout << "Timeline stabilized (Threshold: " << threshold << ").\n\n";
}