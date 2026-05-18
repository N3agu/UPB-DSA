#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <algorithm>
#include "queue.h"

using namespace std;

template <typename T>
class BinaryTree {
public:
    T* pinfo;
    BinaryTree<T>* left_son, * right_son, * parent, * root;

    BinaryTree() {
        pinfo = NULL;
        left_son = right_son = parent = NULL;
        root = this;
    }

    void setInfo(T info) {
        pinfo = new T;
        *pinfo = info;
    }

    void setRoot(BinaryTree<T>* r) {
        root = r;
    }

    void insert(T x) {
        if (pinfo == NULL)
            setInfo(x);
        else
            insert_rec(x);
    }

    void insert_rec(T x) {
        if (x < *pinfo) {
            if (left_son == NULL) {
                left_son = new BinaryTree<T>;
                left_son->setInfo(x);
                left_son->parent = this;
                left_son->root = root;
            }
            else {
                left_son->insert_rec(x);
            }
        }
        else {
            if (right_son == NULL) {
                right_son = new BinaryTree<T>;
                right_son->setInfo(x);
                right_son->parent = this;
                right_son->root = root;
            }
            else {
                right_son->insert_rec(x);
            }
        }
    }

    BinaryTree<T>* find(T x) {
        BinaryTree<T>* rez;
        if (pinfo == NULL) return NULL;
        if ((*pinfo) == x) return this;

        if (left_son != NULL)
            rez = left_son->find(x);
        else
            rez = NULL;

        if (rez != NULL)
            return rez;
        else if (right_son != NULL)
            return right_son->find(x);
        else
            return NULL;
    }

    BinaryTree<T>* findLeaf() {
        if (left_son == NULL && right_son == NULL)
            return this;
        else if (left_son != NULL)
            return left_son->findLeaf();
        else
            return right_son->findLeaf();
    }

    void remove() {
        BinaryTree<T>* leaf;
        leaf = findLeaf();

        if (this == leaf) {
            if (parent == NULL) {
                if (this->pinfo != NULL) delete this->pinfo;
                root->pinfo = NULL;
            }
            else {
                if (parent->left_son == this)
                    parent->left_son = NULL;
                else
                    parent->right_son = NULL;
                delete this->pinfo;
                delete this;
            }
        }
        else {
            if (leaf->parent->left_son == leaf)
                leaf->parent->left_son = NULL;
            else
                leaf->parent->right_son = NULL;

            leaf->parent = parent;
            leaf->left_son = left_son;
            leaf->right_son = right_son;

            delete this->pinfo;
            this->pinfo = leaf->pinfo;
            delete leaf;
        }
    }

    void removeInfo(T x) {
        BinaryTree<T>* t = find(x);
        if (t != NULL)
            t->remove();
    }

    void preOrderTraversal() {
        cout << *pinfo << " ";
        if (left_son != NULL) left_son->preOrderTraversal();
        if (right_son != NULL) right_son->preOrderTraversal();
    }

    void postOrderTraversal() {
        if (left_son != NULL) left_son->postOrderTraversal();
        if (right_son != NULL) right_son->postOrderTraversal();
        cout << *pinfo << " ";
    }

    void inOrderTraversal() {
        if (left_son != NULL) left_son->inOrderTraversal();
        cout << *pinfo << " ";
        if (right_son != NULL) right_son->inOrderTraversal();
    }

    void preOrderTraversalLevels(int level) {
        for (int i = 0; i < level; i++)
            cout << "-";
        cout << *pinfo << endl;

        if (left_son != NULL) left_son->preOrderTraversalLevels(level + 1);
        if (right_son != NULL) right_son->preOrderTraversalLevels(level + 1);
    }

    int height() {
        if (pinfo == NULL) return 0;

        int leftHeight = 0;
        int rightHeight = 0;

        if (left_son != NULL) leftHeight = left_son->height();
        if (right_son != NULL) rightHeight = right_son->height();

        return 1 + max(leftHeight, rightHeight);
    }

    void printLevelOrderTwoQueues() {
        if (pinfo == NULL) return;

        Queue<BinaryTree<T>*> currentLevel, nextLevel;
        currentLevel.enqueue(this);

        while (!currentLevel.isEmpty()) {
            BinaryTree<T>* currentNode = currentLevel.dequeue();

            cout << *(currentNode->pinfo) << " ";

            if (currentNode->left_son != NULL)
                nextLevel.enqueue(currentNode->left_son);

            if (currentNode->right_son != NULL)
                nextLevel.enqueue(currentNode->right_son);

            if (currentLevel.isEmpty()) {
                cout << endl;
                currentLevel = nextLevel;
                nextLevel = Queue<BinaryTree<T>*>();
            }
        }
    }

    void printLevelOrderOneQueue() {
        if (pinfo == NULL) return;

        Queue<BinaryTree<T>*> q;
        q.enqueue(this);

        int nodesInCurrentLevel = 1;
        int nodesInNextLevel = 0;

        while (!q.isEmpty()) {
            BinaryTree<T>* currentNode = q.dequeue();
            nodesInCurrentLevel--;

            cout << *(currentNode->pinfo) << " ";

            if (currentNode->left_son != NULL) {
                q.enqueue(currentNode->left_son);
                nodesInNextLevel++;
            }

            if (currentNode->right_son != NULL) {
                q.enqueue(currentNode->right_son);
                nodesInNextLevel++;
            }

            if (nodesInCurrentLevel == 0) {
                cout << endl;
                nodesInCurrentLevel = nodesInNextLevel;
                nodesInNextLevel = 0;
            }
        }
    }

    void rangeQuery(T x, T y) {
        if (pinfo == NULL) return;

        if (*pinfo > x && left_son != NULL)
            left_son->rangeQuery(x, y);

        if (*pinfo > x && *pinfo < y)
            cout << *pinfo << " ";

        if (*pinfo < y && right_son != NULL)
            right_son->rangeQuery(x, y);
    }
};

#endif