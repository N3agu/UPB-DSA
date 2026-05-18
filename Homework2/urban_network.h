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

public:
    UrbanNetwork();
    ~UrbanNetwork();
    void readInput(const string& filename);
    void solve();
};

#endif