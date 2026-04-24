#ifndef SOURCE_STACK_H
#define SOURCE_STACK_H

#include <iostream>
#define NMAX 50

using std::cout;

template <typename T>
class Source_Stack {
private:
    T stackArray[NMAX];
    int topLevel;
public:
    Source_Stack(): topLevel(-1){}
    ~Source_Stack(){}

    bool isEmpty() {
        return topLevel == -1;
    }


    void push(T item) {
        if (topLevel==NMAX-1) {
            cout<<"Stack is overflow\n";
            return;
        }
        stackArray[++topLevel] = item;
    }

    T pop() {
        if(isEmpty()) {
            cout<<"Stack is empty\n";
            return T();
        }
        return stackArray[topLevel--];
    }

    T peek() {
        if(isEmpty()) {
            cout<<"Stack is empty\n";
            return T();
        }
        return stackArray[topLevel];
    }




};

#endif