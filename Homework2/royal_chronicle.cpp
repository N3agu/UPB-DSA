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

int RoyalChronicle::countLeaves(BinaryTree<Knight>* node) {
    if (node == NULL || node->pinfo == NULL) return 0;
    if (node->left_son == NULL && node->right_son == NULL) return 1;
    return countLeaves(node->left_son) + countLeaves(node->right_son);
}

void RoyalChronicle::printLeaves(BinaryTree<Knight>* node, bool& isFirst) {
    if (node == NULL || node->pinfo == NULL) return;

    printLeaves(node->left_son, isFirst);

    if (node->left_son == NULL && node->right_son == NULL) {
        if (!isFirst) cout << ", ";
        cout << node->pinfo->name << " (" << node->pinfo->braveryScore << ")";
        isFirst = false;
    }

    printLeaves(node->right_son, isFirst);
}

bool RoyalChronicle::isBalanced(BinaryTree<Knight>* node) {
    if (node == NULL || node->pinfo == NULL) return true;

    int leftHeight = (node->left_son != NULL) ? node->left_son->height() : 0;
    int rightHeight = (node->right_son != NULL) ? node->right_son->height() : 0;

    if (std::abs(leftHeight - rightHeight) <= 1 &&
        isBalanced(node->left_son) &&
        isBalanced(node->right_son)) {
        return true;
    }

    return false;
}

void RoyalChronicle::archiveStructureReport() {
    cout << "=== 4 ===\n";
    cout << "Height of the Archive: " << registry->height() << "\n";

    cout << "Leaf nodes (knights with no subordinates): " << countLeaves(registry) << "\n";
    bool isFirst = true;
    printLeaves(registry, isFirst);
    cout << "\n";

    if (isBalanced(registry)) {
        cout << "The Archive is balanced.\n";
    }
    else {
        cout << "The Archive is unbalanced.\n";
    }
}

void RoyalChronicle::queryRange(BinaryTree<Knight>* node, int L, int R, int& totalBattles, bool& found) {
    if (node == NULL || node->pinfo == NULL) return;

    if (node->pinfo->braveryScore > L) {
        queryRange(node->left_son, L, R, totalBattles, found);
    }

    if (node->pinfo->braveryScore >= L && node->pinfo->braveryScore <= R) {
        cout << node->pinfo->name << " (" << node->pinfo->braveryScore << ") | House "
            << node->pinfo->house << " | " << node->pinfo->battlesWon << " battles\n";
        totalBattles += node->pinfo->battlesWon;
        found = true;
    }

    if (node->pinfo->braveryScore < R) {
        queryRange(node->right_son, L, R, totalBattles, found);
    }
}

void RoyalChronicle::processRangeQuery() {
    cout << "=== 5 ===\n";
    cout << "Knights with bravery in [" << L << ", " << R << "]:\n";

    int totalBattles = 0;
    bool found = false;

    queryRange(registry, L, R, totalBattles, found);

    if (!found) {
        cout << "No knights found in this bravery range.\n";
    }
    else {
        cout << "Total battles won by knights in range: " << totalBattles << "\n";
    }
}

void RoyalChronicle::solve() {
    performTraversals();
    houseAndExtremes();
    archiveStructureReport();
    processRangeQuery();
}