#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "linked_list.h"
#include "queue.h"

template<typename TedgeInfo>
struct list_elem_info {
    int node;
    TedgeInfo edgeInfo;
};

template<typename TnodeInfo, typename TedgeInfo>
class Graph {
public:
    int N;
    LinkedList<struct list_elem_info<TedgeInfo> >* L;
    TnodeInfo* nodeInfo;

    Graph(int numNodes) {
        N = numNodes;
        L = new LinkedList<struct list_elem_info<TedgeInfo> >[N];
        nodeInfo = new TnodeInfo[N];
    }

    void setNodeInfo(int i, TnodeInfo info) {
        nodeInfo[i] = info;
    }

    TnodeInfo getNodeInfo(int i) {
        return nodeInfo[i];
    }

    void addEdge(int i, int j) {
        struct list_elem_info<TedgeInfo> lei_i, lei_j;
        lei_i.node = j;
        lei_j.node = i;

        L[i].addFirst(lei_i);
        L[j].addFirst(lei_j);
    }

    void addDirectedEdge(int from, int to, TedgeInfo edgeData) {
        struct list_elem_info<TedgeInfo> lei_to;
        lei_to.node = to;
        lei_to.edgeInfo = edgeData;

        L[from].addFirst(lei_to);
    }

    void removeEdge(int i, int j) {
        struct list_elem<struct list_elem_info<TedgeInfo> >* p;

        p = L[i].pfirst;
        while (p != NULL) {
            if (p->info.node == j) break;
            p = p->next;
        }
        L[i].removeNode(p);

        p = L[j].pfirst;
        while (p != NULL) {
            if (p->info.node == i) break;
            p = p->next;
        }
        L[j].removeNode(p);
    }

    void removeDirectedEdge(int from, int to) {
        Node<struct list_elem_info<TedgeInfo> >* p;

        p = L[from].pfirst;
        while (p != NULL) {
            if (p->info.node == to) {
                L[from].removeNode(p);
                break;
            }
            p = p->next;
        }
    }

    void setEdgeInfo(int i, int j, TedgeInfo info) {
        struct list_elem<struct list_elem_info<TedgeInfo> >* p;
        p = L[i].pfirst;
        while (p != NULL) {
            if (p->info.node == j) {
                p->info.edgeInfo = info;
                break;
            }
            p = p->next;
        }
    }

    TedgeInfo getEdgeInfo(int i, int j) {
        struct list_elem<struct list_elem_info<TedgeInfo> >* p;
        p = L[i].pfirst;
        while (p != NULL) {
            if (p->info.node == j)
                return p->info.edgeInfo;
            p = p->next;
        }
        return TedgeInfo();
    }

    ~Graph() {
        delete[] nodeInfo;
        for (int i = 0; i < N; i++) {
            while (!L[i].isEmpty()) {
                L[i].removeFirst();
            }
        }
        delete[] L;
    }
};

#endif