#ifndef ROYAL_CHRONICLE_H
#define ROYAL_CHRONICLE_H

#include <string>
#include <iostream>
#include "binary_tree.h"

using std::string;

struct Knight {
    string name;
    int braveryScore;
    string house;
    int battlesWon;

    bool operator<(const Knight& other) const {
        return braveryScore < other.braveryScore;
    }
    bool operator>(const Knight& other) const {
        return braveryScore > other.braveryScore;
    }
    bool operator==(const Knight& other) const {
        return braveryScore == other.braveryScore;
    }
    friend std::ostream& operator<<(std::ostream& os, const Knight& k) {
        os << k.name << " (" << k.braveryScore << ")";
        return os;
    }
};

class RoyalChronicle {
private:
    BinaryTree<Knight>* registry;
    int N;
    string houseQuery;
    int L, R;
    int K;
    string nameLCA1, nameLCA2;
    string banishName;

    void clearRegistry(BinaryTree<Knight>* node);
    void performTraversals();
    void printHouseKnights(BinaryTree<Knight>* node, const string& house);
    void printNewestRecruit();
    void printChampion();
    void houseAndExtremes();
    int countLeaves(BinaryTree<Knight>* node);
    void printLeaves(BinaryTree<Knight>* node, bool& isFirst);
    bool isBalanced(BinaryTree<Knight>* node);
    void archiveStructureReport();
    void queryRange(BinaryTree<Knight>* node, int L, int R, int& totalBattles, bool& found);
    void processRangeQuery();
    Knight* findByName(BinaryTree<Knight>* node, const string& name);
    void findKthValorous(BinaryTree<Knight>* node, int& k, Knight*& result);
    BinaryTree<Knight>* findLCA(BinaryTree<Knight>* node, int val1, int val2);
    void politicalQueries();
    void banishKnight();

public:
    RoyalChronicle();
    ~RoyalChronicle();
    void readInput(const string& filename);
    void solve();
};

#endif