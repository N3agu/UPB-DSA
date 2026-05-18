#include "urban_network.h"
#include <iostream>

using std::cin;
using std::cout;

UrbanNetwork::UrbanNetwork() : g(NULL), N(0), M(0) {}

UrbanNetwork::~UrbanNetwork() {
    if (g != NULL) {
        delete g;
    }
}

void UrbanNetwork::readInput(const string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        cout << "Error: Could not open file '" << filename << "'. Please ensure it exists in the directory.\n";
        exit(1);
    }

    fin >> N >> M;
    g = new Graph<int, Road>(N);
    indexToArea.resize(N);

    for (int i = 0; i < N; ++i) {
        fin >> indexToArea[i];
        areaToIndex[indexToArea[i]] = i;
        g->setNodeInfo(i, i);
    }

    for (int i = 0; i < M; ++i) {
        string u, v;
        Road r;
        fin >> u >> v >> r.time >> r.risk >> r.energy;
        g->addDirectedEdge(areaToIndex[u], areaToIndex[v], r);
    }

    int S;
    fin >> S;
    chargingStations.resize(S);
    for (int i = 0; i < S; ++i) {
        fin >> chargingStations[i];
    }

    int C;
    fin >> C;
    criticalZones.resize(C);
    for (int i = 0; i < C; ++i) {
        fin >> criticalZones[i];
    }

    int R;
    fin >> R;
    robots.resize(R);
    for (int i = 0; i < R; ++i) {
        fin >> robots[i].start >> robots[i].autonomy >> robots[i].maxRisk;
    }

    fin >> queryBase;
    fin.close();
}

void UrbanNetwork::findMostExposedArea() {
    vector<int> inDegree(N, 0);
    for (int i = 0; i < N; ++i) {
        Node<list_elem_info<Road>>* p = g->L[i].pfirst;
        while (p != NULL) {
            inDegree[p->info.node]++;
            p = p->next;
        }
    }

    int maxIn = -1;
    for (int i = 0; i < N; ++i) {
        if (inDegree[i] > maxIn) {
            maxIn = inDegree[i];
        }
    }

    cout << "Most exposed area(s):\n";
    for (int i = 0; i < N; ++i) {
        if (inDegree[i] == maxIn) {
            cout << indexToArea[i] << " with " << maxIn << " incoming roads\n";
        }
    }
}

void UrbanNetwork::checkNetworkValidity() {
    vector<vector<int>> adj(N);
    for (int i = 0; i < N; ++i) {
        Node<list_elem_info<Road>>* p = g->L[i].pfirst;
        while (p != NULL) {
            int to = p->info.node;
            adj[i].push_back(to);
            adj[to].push_back(i);
            p = p->next;
        }
    }

    vector<bool> visited(N, false);
    vector<vector<int>> components;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            vector<int> currentComponent;
            vector<int> stack;
            stack.push_back(i);
            visited[i] = true;

            while (!stack.empty()) {
                int node = stack.back();
                stack.pop_back();
                currentComponent.push_back(node);

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        stack.push_back(neighbor);
                    }
                }
            }
            components.push_back(currentComponent);
        }
    }

    if (components.size() == 1) {
        cout << "The network is valid when road directions are ignored.\n";
    }
    else {
        cout << "The network is not valid. Separate connected components:\n";
        for (size_t i = 0; i < components.size(); ++i) {
            cout << "Component " << i + 1 << ": ";
            for (int node : components[i]) {
                cout << indexToArea[node] << " ";
            }
            cout << "\n";
        }
    }
}

void UrbanNetwork::mapNetwork() {
    for (int i = 0; i < N; ++i) {
        Node<list_elem_info<Road>>* p = g->L[i].pfirst;
        while (p != NULL) {
            int to = p->info.node;
            Road r = p->info.edgeInfo;

            cout << "Establishing link: " << indexToArea[i] << " ---> " << indexToArea[to] << "\n";
            cout << "  [Time: " << r.time << " | Risk: " << r.risk << " | Energy: " << r.energy << "]\n";

            p = p->next;
        }
    }
}

void UrbanNetwork::generateGraphviz() {
    std::ofstream out("network_graph.dot");
    if (!out) {
        cout << "Error: Could not create .dot file.\n";
        return;
    }

    out << "digraph UrbanNetwork {\n";
    out << "  node [shape=box, style=filled, fillcolor=lightblue];\n";

    for (int i = 0; i < N; ++i) {
        Node<list_elem_info<Road>>* p = g->L[i].pfirst;
        while (p != NULL) {
            int to = p->info.node;
            Road r = p->info.edgeInfo;

            out << "  \"" << indexToArea[i] << "\" -> \"" << indexToArea[to]
                << "\" [label=\"T:" << r.time << " R:" << r.risk << " E:" << r.energy << "\"];\n";

            p = p->next;
        }
    }
    out << "}\n";
    out.close();

    cout << "Graphviz script generated: 'network_graph.dot'.\n";
    cout << "Navigate to https://dreampuf.github.io/GraphvizOnline/ and upload the '.dot' file to get the visual representation.\n";
}

void UrbanNetwork::findBlockedAreas() {
    vector<int> inDegree(N, 0);
    vector<int> outDegree(N, 0);

    for (int i = 0; i < N; ++i) {
        Node<list_elem_info<Road>>* p = g->L[i].pfirst;
        while (p != NULL) {
            outDegree[i]++;
            inDegree[p->info.node]++;
            p = p->next;
        }
    }

    vector<string> blockedAreas;
    for (int i = 0; i < N; ++i) {
        if (inDegree[i] > 0 && outDegree[i] == 0) {
            blockedAreas.push_back(indexToArea[i]);
        }
    }

    cout << "Blocked areas:\n";
    if (blockedAreas.empty()) {
        cout << "No blocked areas detected.\n";
    }
    else {
        for (size_t i = 0; i < blockedAreas.size(); ++i) {
            cout << blockedAreas[i] << "\n";
        }
    }
}

void UrbanNetwork::findInaccessibleAreas() {
    if (areaToIndex.find(queryBase) == areaToIndex.end()) {
        return;
    }

    int startNode = areaToIndex[queryBase];
    vector<bool> visited(N, false);
    vector<int> q;

    q.push_back(startNode);
    visited[startNode] = true;

    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        Node<list_elem_info<Road>>* p = g->L[u].pfirst;
        while (p != NULL) {
            int v = p->info.node;
            if (!visited[v]) {
                visited[v] = true;
                q.push_back(v);
            }
            p = p->next;
        }
    }

    vector<string> inaccessible;
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            inaccessible.push_back(indexToArea[i]);
        }
    }

    if (inaccessible.empty()) {
        cout << "From base " << queryBase << ", all areas are reachable.\n";
    }
    else {
        cout << "Areas inaccessible from " << queryBase << ":\n";
        for (size_t i = 0; i < inaccessible.size(); ++i) {
            cout << inaccessible[i] << "\n";
        }
    }
}

void UrbanNetwork::dfsRobotPath(int u, int currentEnergy, int currentTime, int maxRisk, int maxEnergy,
    vector<bool>& visited, vector<int>& currentPath, BestPath& best, const vector<bool>& isCritical) {
    if (currentEnergy > maxEnergy) return;

    if (isCritical[u]) {
        if (currentTime < best.time || (currentTime == best.time && currentEnergy < best.energy)) {
            best.time = currentTime;
            best.energy = currentEnergy;
            best.path = currentPath;
            best.targetZone = u;
        }
    }

    Node<list_elem_info<Road>>* p = g->L[u].pfirst;
    while (p != NULL) {
        int v = p->info.node;
        Road r = p->info.edgeInfo;

        if (!visited[v] && r.risk <= maxRisk && currentEnergy + r.energy <= maxEnergy) {
            visited[v] = true;
            currentPath.push_back(v);

            dfsRobotPath(v, currentEnergy + r.energy, currentTime + r.time, maxRisk, maxEnergy,
                visited, currentPath, best, isCritical);

            currentPath.pop_back();
            visited[v] = false;
        }
        p = p->next;
    }
}

void UrbanNetwork::calculateRobotPaths() {
    vector<bool> isCritical(N, false);
    for (size_t i = 0; i < criticalZones.size(); ++i) {
        if (areaToIndex.find(criticalZones[i]) != areaToIndex.end()) {
            isCritical[areaToIndex[criticalZones[i]]] = true;
        }
    }

    for (size_t i = 0; i < robots.size(); ++i) {
        cout << "Robot " << i + 1 << ":\n";
        cout << "Initial position: " << robots[i].start << "\n";
        cout << "Autonomy: " << robots[i].autonomy << "\n";
        cout << "Maximum accepted risk: " << robots[i].maxRisk << "\n";

        if (areaToIndex.find(robots[i].start) == areaToIndex.end()) {
            cout << "No valid direct path to a critical zone.\n";
            continue;
        }

        int startNode = areaToIndex[robots[i].start];
        BestPath best;
        vector<bool> visited(N, false);
        vector<int> currentPath;

        visited[startNode] = true;
        currentPath.push_back(startNode);

        dfsRobotPath(startNode, 0, 0, robots[i].maxRisk, robots[i].autonomy, visited, currentPath, best, isCritical);

        if (best.targetZone == -1) {
            cout << "No valid direct path to a critical zone.\n";
        }
        else {
            cout << "Optimal direct path to a critical zone:\n";
            for (size_t j = 0; j < best.path.size(); ++j) {
                cout << indexToArea[best.path[j]];
                if (j < best.path.size() - 1) cout << " -> ";
            }
            cout << "\nTotal travel time: " << best.time << "\n";
            cout << "Energy consumed: " << best.energy << "\n";
            cout << "Critical zone reached: " << indexToArea[best.targetZone] << "\n";
        }
    }
}

void UrbanNetwork::solve() {
    mapNetwork();
    generateGraphviz();
    findMostExposedArea();
    checkNetworkValidity();
    findBlockedAreas();
    findInaccessibleAreas();
    calculateRobotPaths();
}