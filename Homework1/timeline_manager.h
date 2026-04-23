#ifndef TIMELINE_MANAGER_H
#define TIMELINE_MANAGER_H

#include <string>
#include "linked_list.h"

using std::string;

struct Event {
    int id;
    string description;
    int year;
    int impact;
};

class TimelineManager {
    private:
        LinkedList<Event> timeline;
        Node<Event>* findEventNode(int id);
        void removeEventNode(Node<Event>* node);

    public:
        TimelineManager();
        void recordAncientEvent(Event e);
        void recordRecentEvent(Event e);
        void insertEventBetween(int leftId, int rightId, Event e);
        void eraseCorruptedEvent(int id);
        void relocateEvent(int idToMove, int newNeighborId, bool before);
        void displayChronology();
        int computeTotalImpact();
        void stabilizeTimeline(int threshold);
};

#endif