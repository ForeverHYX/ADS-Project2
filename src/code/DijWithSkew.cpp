#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <time.h>
#include <random>
#include <chrono>
#include "HeapLibrary/SkewHeap.hpp"

using namespace std;

const int MAX_NODES = 1100000;
const int MAX_EDGES = 2800000;

struct Edge {
    int to, distance, next;
};

Edge edges[MAX_EDGES];
int head[MAX_NODES], distances[MAX_NODES], edgeCount;
bool visited[MAX_NODES];
int numNodes, numEdges, startNode;

// 用于记录insert和delete_min的累计时间
double totalInsertTime = 0;
double totalDeleteMinTime = 0;
int insertCount = 0;
int deleteMinCount = 0;

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
            // 记录insert操作的时间
            auto startInsert = chrono::high_resolution_clock::now();
            minHeap.insert({distances[y], y});
            auto stopInsert = chrono::high_resolution_clock::now();
            totalInsertTime += chrono::duration<double>(stopInsert - startInsert).count();
            insertCount++;
        }
    }
}

inline void dijkstra(int startNode) {
    distances[startNode] = 0;
    
    auto startInsert = chrono::high_resolution_clock::now();
    minHeap.insert({0, startNode});
    auto stopInsert = chrono::high_resolution_clock::now();
    totalInsertTime += chrono::duration<double>(stopInsert - startInsert).count();
    insertCount++;

    while (minHeap.root != nullptr) {
        auto startDelete = chrono::high_resolution_clock::now();
        auto current = minHeap.find_min();
        minHeap.delete_min();
        auto stopDelete = chrono::high_resolution_clock::now();
        totalDeleteMinTime += chrono::duration<double>(stopDelete - startDelete).count();
        deleteMinCount++;

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

double duration;
int main() {
    srand((unsigned int)time(0));
    int startnode, destination;
    double once_time;
    duration = 0;

    for (int k = 1; k <= 10; k++) {
        FILE *file = fopen("FLA.txt", "r"); // biggest.txt   SAMPLE.txt   linear_graph.txt   quadratic_root_graph.txt    quadratic_graph.txt
        fscanf(file, "%d %d\n", &numNodes, &numEdges);
        for (int i = 1; i <= numNodes; ++i) {
            distances[i] = numeric_limits<int>::max();
            head[i] = 0;
            visited[i] = false;
        }
        edgeCount = 0;
        for (int i = 0; i < numEdges; ++i) {
            char a;
            int u, v, d;
            fscanf(file, "%c %d %d %d\n", &a, &u, &v, &d);

            addEdge(u, v, d);
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, numNodes);

        startnode = dis(gen);
        do {
            destination = dis(gen);
        } while (destination == startnode);

        auto start = chrono::high_resolution_clock::now();
        dijkstra(startnode);
        auto stop = chrono::high_resolution_clock::now();
        once_time = chrono::duration<double>(stop - start).count();

        duration += once_time;

        printf("the length of shortest path from %d to %d is %d\n", startnode, destination, distances[destination]);
    }

    double average_time = duration / 10;

    if (average_time >= 1.0) {
        printf("this function costs average %.6lf s\n", average_time);
    } else {
        printf("this function costs average %.6lf ms\n", average_time * 1000);
    }

    if (insertCount > 0) {
        printf("Average insert time: %.6lf ms\n", (totalInsertTime / insertCount) * 1000);
    }
    if (deleteMinCount > 0) {
        printf("Average delete_min time: %.6lf ms\n", (totalDeleteMinTime / deleteMinCount) * 1000);
    }

    return 0;
}
