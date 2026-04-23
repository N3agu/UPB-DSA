#ifndef SOURCE_QUEUE_CIRCULAR_H
#define SOURCE_QUEUE_CIRCULAR_H

#include <iostream>
#include <stdexcept>

#define NMAX 5
template<typename T> class Queue_Circular {
private:
    T queueArray[NMAX];
    int head, tail, size;
public:
    void enqueue(T x) {
        if (size == NMAX) {
            std::cerr << "Queue is full!" << std::endl;
            return;
        }
        queueArray[tail] = x;
        tail = (tail + 1) % NMAX;
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty!" << std::endl;
            return T();
        }
        T x = queueArray[head];
        head = (head + 1) % NMAX;
        size--;
        return x;
    }
    T peek() {
        if (isEmpty()) {
            std::cerr << "Queue is empty!" << std::endl;
            return T();
        }
        return queueArray[head];
    }

    bool isEmpty() {
        return (size == 0);
    }

    Queue_Circular() {
        head = tail = size = 0;
    }
};

#endif