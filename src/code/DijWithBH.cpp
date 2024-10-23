#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <cstring>
#include <random>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>
#include "HeapLibrary/BinaryHeap.hpp" // Include the heap library we've written

using namespace std;

const int MAX_NODES = 5000000;
const int MAX_EDGES = 10000000;// Max nodes

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
} // Use linked list to store edges

BinaryHeap<pair<int, int>> minHeap; // Create a heap using binary heap

inline void relax(int x, int y, int d) { // Relax to update minimum
    if (distances[y] > distances[x] + d) {
        distances[y] = distances[x] + d;
        if (!visited[y]) {
            minHeap.insert({distances[y], y});
        }
    }
}

inline void dijkstra(int startNode) { //Dijkstra algorithm
    distances[startNode] = 0;
    minHeap.insert({0, startNode});

    while (!minHeap.heap.empty()) {
        auto current = minHeap.find_min();
        minHeap.delete_min(); //findmin and delete it

        int x = current.second;
        if (visited[x]) continue; // If visited means it's not the smallest, so continue

        visited[x] = true;

        for (int i = head[x]; i != 0; i = edges[i].next) {
            int y = edges[i].to;
            relax(x, y, edges[i].distance); // Relax all related edges
        }
    }
}

int main()
{
    srand((unsigned int)time(0));
    vector<pair<int, double>> results; // Use pairs to store result (numnodes, averagetime)
    ofstream outputFile("resultsBH.txt");

    for (int k = 1; k <= 4; k++)
    {
        string filename = "graphwithdiffnode/quadratic_graph" + to_string(k) + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open " << filename << endl;
            continue;
        }

        file >> numNodes >> numEdges;
        for (int i = 1; i <= numNodes; ++i) {// Initialization
            distances[i] = numeric_limits<int>::max();
            head[i] = 0;
            visited[i] = false;
        }
        edgeCount = 0;
        for (int i = 0; i < numEdges; ++i) { // Add all edges to create the graph
            char a;
            int u, v, d;
            file >> a >> u >> v >> d;
            addEdge(u, v, d);
        }

        random_device rd;  
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, numNodes); // use random to generate high-quality random numbers
        int startnode = dis(gen);
        int destination;
        do {
            destination = dis(gen);
        } while (destination == startnode);

        auto start = chrono::high_resolution_clock::now(); // high-resolution time counting
        dijkstra(startnode);
        auto stop = chrono::high_resolution_clock::now();
        double once_time = chrono::duration<double>(stop - start).count() * 1000;

        results.push_back({numNodes, once_time});
    }

    sort(results.begin(), results.end()); // output in numnode-order

    for (const auto& result : results) {
        outputFile << result.first << " " << result.second << endl;
    }

    outputFile.close();
    return 0;
}
