#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include "Heap.hpp"

using namespace std;

const int MAX_NODES = 100010;
const int MAX_EDGES = 500010;

struct Edge {
    int to, distance, next;
};

Edge edges[MAX_EDGES];
int head[MAX_NODES], distances[MAX_NODES], edgeCount;
bool visited[MAX_NODES];
int numNodes, numEdges, startNode;

inline void addEdge(int u, int v, int d) {
    edgeCount++;
    edges[edgeCount].distance = d;
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

Heap<node> minHeap;

inline void relax(int x, int y, int d) {
    if (distances[y] > distances[x] + d) {
        distances[y] = distances[x] + d;
        if (!visited[y]) {
            minHeap.insert((node){distances[y], y});
        }
    }
}

inline void dijkstra() {
    distances[startNode] = 0;
    minHeap.insert((node){0, startNode});
    
    while (!minHeap.heap.empty()) {
        node currentNode = minHeap.find_min();
        minHeap.delete_min();
        
        int x = currentNode.pos;
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
    scanf("%d%d%d", &numNodes, &numEdges, &startNode);
    for (int i = 1; i <= numNodes; ++i)
        distances[i] = numeric_limits<int>::max();
    for (int i = 0; i < numEdges; ++i) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        addEdge(u, v, d);
    }
    dijkstra();
    for (int i = 1; i <= numNodes; i++)
        printf("%d ", distances[i]);
    return 0;
}
