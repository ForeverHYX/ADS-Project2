/*
Using priority queue to create a new heap, other details are the same as DjiWithBH.cpp, see the comments there
*/
#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <time.h>
#include <random>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>
#include "HeapLibrary/Heap.hpp"

using namespace std;

const long MAX_NODES = 25000000;
const long MAX_EDGES = 60000000;

struct Edge {
    int to, distance, next;
};

struct Result {
    int nodeCount;
    double time;
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

Heap<node> minHeap;

inline void relax(int x, int y, int d) {
    if (distances[y] > distances[x] + d) {
        distances[y] = distances[x] + d;
        if (!visited[y]) {
            minHeap.insert((node){distances[y], y});
        }
    }
}

inline void dijkstra(int startNode) {
    distances[startNode] = 0;
    minHeap.insert((node){0, startNode});

    while (!minHeap.heap.empty()) {
        node currentNode = minHeap.find_min();
        minHeap.delete_min();

        long int x = currentNode.pos;
        if (visited[x]) continue;

        visited[x] = true;

        for (int i = head[x]; i; i = edges[i].next) {
            int y = edges[i].to;
            relax(x, y, edges[i].distance);
        }
    }
}

int main()
{
    srand((unsigned int)time(0));
    vector<pair<int, double>> results;
    ofstream outputFile("resultsSTL.txt");

    for (int k = 1; k <= 4; k++)
    {
        string filename = "graphwithdiffnode/quadratic_graph" + to_string(k) + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open " << filename << endl;
            continue;
        }

        file >> numNodes >> numEdges;
        for (int i = 1; i <= numNodes; ++i) {
            distances[i] = numeric_limits<int>::max();
            head[i] = 0;
            visited[i] = false;
        }
        edgeCount = 0;
        for (int i = 0; i < numEdges; ++i) {
            char a;
            int u, v, d;
            file >> a >> u >> v >> d;
            addEdge(u, v, d);
        }

        random_device rd;  
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, numNodes);
        int startnode = dis(gen);
        int destination;
        do {
            destination = dis(gen);
        } while (destination == startnode);

        auto start = chrono::high_resolution_clock::now();
        dijkstra(startnode);
        auto stop = chrono::high_resolution_clock::now();
        double once_time = chrono::duration<double>(stop - start).count() * 1000;

        results.push_back({numNodes, once_time});
    }

    sort(results.begin(), results.end());

    for (const auto& result : results) {
        outputFile << result.first << " " << result.second << endl;
    }

    outputFile.close();
    return 0;
}