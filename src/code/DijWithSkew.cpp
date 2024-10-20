#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include "SkewHeap.hpp"

using namespace std;

const int MAX_NODES = 100010;
const int MAX_EDGES = 500010;

struct Edge {
    int to, distance, next;
};

Edge edges[MAX_EDGES];
int head[MAX_NODES], distances[MAX_NODES], edgeCount;
bool visited[MAX_NODES];
int numNodes, numEdges;

inline void addEdge(int u, int v, int d) {
    edgeCount++;
    edges[edgeCount].distance = d;
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

SkewHeap<pair<int, int>> minHeap;

inline void relax(int x, int y, int d) {
    if (distances[y] > distances[x] + d) {
        distances[y] = distances[x] + d;
        if (!visited[y]) {
            minHeap.insert({distances[y], y});
        }
    }
}

inline void dijkstra(int startNode) {
    distances[startNode] = 0;
    minHeap.insert({0, startNode});
    
    while (minHeap.root != nullptr) {
        auto current = minHeap.find_min();
        minHeap.delete_min();
        
        int x = current.second;
        if (visited[x])
            continue;

        visited[x] = true;

        for (int i = head[x]; i; i = edges[i].next) {
            int y = edges[i].to;
            relax(x, y, edges[i].distance);
        }
    }
}

int main() {
    int startNode, endNode;
    scanf("%d%d%d", &numNodes, &numEdges, &startNode);
    for (int i = 1; i <= numNodes; ++i)
        distances[i] = numeric_limits<int>::max();
    
    for (int i = 0; i < numEdges; ++i) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        addEdge(u, v, d);
    }
    
    dijkstra(startNode);
    
    for (int i = 1; i <= numNodes; i++)
        printf("%d ", distances[i]);
    
    return 0;
}
