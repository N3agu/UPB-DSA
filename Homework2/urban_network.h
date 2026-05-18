#ifndef URBAN_NETWORK_H
#define URBAN_NETWORK_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include "graph.h"

using std::string;
using std::vector;
using std::map;

struct Road {
    int time;
    int risk;
    int energy;
};

struct Robot {
    string start;
    int autonomy;
    int maxRisk;
};

struct BestPath {
    vector<int> path;
    int time = INT_MAX;
    int energy = INT_MAX;
    int targetZone = -1;
};

class UrbanNetwork {
private:
    Graph<int, Road>* g;
    map<string, int> areaToIndex;
    vector<string> indexToArea;
    int N, M;
    vector<string> chargingStations;
    vector<string> criticalZones;
    vector<Robot> robots;
    string queryBase;

    void mapNetwork();
    void generateGraphviz();
    void findMostExposedArea();
    void checkNetworkValidity();
    void findBlockedAreas();
    void findInaccessibleAreas();
    void dfsRobotPath(int u, int currentEnergy, int currentTime, int maxRisk, int maxEnergy, vector<bool>& visited, vector<int>& currentPath, BestPath& best, const vector<bool>& isCritical);
    void calculateRobotPaths();

public:
    UrbanNetwork();
    ~UrbanNetwork();
    void readInput(const string& filename);
    void solve();
};

#endif