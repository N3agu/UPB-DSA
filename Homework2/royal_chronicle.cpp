#include "royal_chronicle.h"
#include <fstream>
#include <iostream>

using std::cout;

RoyalChronicle::RoyalChronicle() {
    registry = new BinaryTree<Knight>();
}

void RoyalChronicle::clearRegistry(BinaryTree<Knight>* node) {
    if (node == NULL) return;

    clearRegistry(node->left_son);
    clearRegistry(node->right_son);

    if (node->pinfo != NULL) {
        delete node->pinfo;
    }
    delete node;
}

RoyalChronicle::~RoyalChronicle() {
    if (registry != NULL) {
        clearRegistry(registry);
        registry = NULL;
    }
}

void RoyalChronicle::readInput(const string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        cout << "Error: Could not open file '" << filename << "'.\n";
        exit(1);
    }

    fin >> N;
    for (int i = 0; i < N; ++i) {
        Knight k;
        fin >> k.name >> k.braveryScore >> k.house >> k.battlesWon;
        registry->insert(k);
    }

    fin >> houseQuery;
    fin >> L >> R;
    fin >> K;
    fin >> nameLCA1 >> nameLCA2;
    fin >> banishName;

    fin.close();
}

void RoyalChronicle::performTraversals() {
    cout << "=== 1 & 2 ===\n";
    cout << "In-order (Tournament Ranking):\n";
    registry->inOrderTraversal();
    cout << "\n\nPre-order (Royal Proclamation):\n";
    registry->preOrderTraversal();
    cout << "\n\nPost-order (Tribute Collection):\n";
    registry->postOrderTraversal();
    cout << "\n\n";
}

void RoyalChronicle::printHouseKnights(BinaryTree<Knight>* node, const string& house) {
    if (node == NULL || node->pinfo == NULL) return;

    printHouseKnights(node->left_son, house);

    if (node->pinfo->house == house) {
        cout << node->pinfo->name << " | bravery: " << node->pinfo->braveryScore
            << " | battles won: " << node->pinfo->battlesWon << "\n";
    }

    printHouseKnights(node->right_son, house);
}

void RoyalChronicle::printNewestRecruit() {
    BinaryTree<Knight>* curr = registry;
    if (curr == NULL || curr->pinfo == NULL) return;

    while (curr->left_son != NULL) {
        curr = curr->left_son;
    }

    Knight* k = curr->pinfo;
    cout << "Newest Recruit (lowest bravery): " << k->name << " | bravery: "
        << k->braveryScore << " | " << k->house << " | " << k->battlesWon << " battles\n";
}

void RoyalChronicle::printChampion() {
    BinaryTree<Knight>* curr = registry;
    if (curr == NULL || curr->pinfo == NULL) return;

    while (curr->right_son != NULL) {
        curr = curr->right_son;
    }

    Knight* k = curr->pinfo;
    cout << "Champion of the Realm (highest): " << k->name << " | bravery: "
        << k->braveryScore << " | " << k->house << " | " << k->battlesWon << " battles\n";
}

void RoyalChronicle::houseAndExtremes() {
    cout << "=== 3 ===\n";
    cout << "Knights of House " << houseQuery << " (ascending bravery):\n";
    printHouseKnights(registry, houseQuery);
    printNewestRecruit();
    printChampion();
    cout << "\n";
}

void RoyalChronicle::solve() {
    performTraversals();
    houseAndExtremes();
}