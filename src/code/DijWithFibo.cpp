#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include "FibonacciHeap.hpp"

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
FibonacciNode<pair<int, int>>* nodesInHeap[MAX_NODES];  // 保存每个节点在堆中的位置

inline void addEdge(int u, int v, int d) {
    edgeCount++;
    edges[edgeCount].distance = d;
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

FibonacciHeap<pair<int, int>> minHeap;

inline void relax(int x, int y, int d) {
    if (distances[y] > distances[x] + d) {
        distances[y] = distances[x] + d;
        if (!visited[y]) {
            pair<int, int> t = {distances[y], y};
            if (nodesInHeap[y] == nullptr) {
                nodesInHeap[y] = new FibonacciNode<pair<int, int>>(t);
                minHeap.insert(t);
            } else {
                minHeap.decrease_key(nodesInHeap[y], t);
            }
        }
    }
}

inline void dijkstra() {
    distances[startNode] = 0;
    pair<int, int> t = {0, startNode};
    minHeap.insert(t);
    nodesInHeap[startNode] = new FibonacciNode<pair<int, int>>(t);
    
    while (minHeap.heap != nullptr) {
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
