#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <time.h>
#include <random>
#include "BinomialHeap.hpp"

using namespace std;

const long int MAX_NODES = 25000000;
const long int MAX_EDGES = 60000000;

struct Edge
{
    int to, distance, next;
};

Edge edges[MAX_EDGES];
int head[MAX_NODES], distances[MAX_NODES], edgeCount;
bool visited[MAX_NODES];
int numNodes, numEdges;

inline void addEdge(int u, int v, int d)
{
    edgeCount++;
    edges[edgeCount].distance = d;
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

BinomialHeap<pair<int, int>> minHeap;

inline void relax(int x, int y, int d)
{
    if (distances[y] > distances[x] + d)
    {
        distances[y] = distances[x] + d;
        if (!visited[y])
        {
            minHeap.insert({distances[y], y});
        }
    }
}

inline void dijkstra(int startNode)
{
    distances[startNode] = 0;
    minHeap.insert({0, startNode});

    while (minHeap.root_node != nullptr)
    {
        auto current = minHeap.find_min(); // Find minimum distance node
        minHeap.delete_min();

        int x = current.second; // current.second holds the vertex
        if (visited[x])
            continue;

        visited[x] = true;

        for (int i = head[x]; i; i = edges[i].next)
        {
            int y = edges[i].to;
            relax(x, y, edges[i].distance);
        }
    }
}
clock_t start, stop;
double duration;
int main()
{
    int startnode, destination;
    double once_time;
    duration = 0;

    for (int k = 1; k <= 1000; k++)
    {

        FILE *file = fopen("linear_graph.txt", "r"); // biggest.txt   SAMPLE.txt   linear_graph.txt   quadratic_root_graph.txt    quadratic_graph.txt
        fscanf(file, "%d %d\n", &numNodes, &numEdges);
        for (int i = 1; i <= numNodes; ++i)
        {
            distances[i] = numeric_limits<int>::max();
            head[i] = 0;
            visited[i] = false;
        }
        edgeCount = 0;
        for (int i = 0; i < numEdges; ++i)
        {
            char a;
            int u, v, d;
            fscanf(file, "%c %d %d %d\n", &a, &u, &v, &d);

            addEdge(u, v, d);
        }

        random_device rd;  
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, numNodes);

        int startnode = dis(gen);
        int destination;
        do
        {
            destination = dis(gen);
        } while (destination == startnode);

        start = clock();
        dijkstra(startnode);
        stop = clock();
        once_time = ((double)(stop - start)) / CLK_TCK;

        duration += once_time;

        printf("the length of shortest path from %d to %d is %d\n", startnode, destination, distances[destination]);
    }

    printf("this function costs average %lf sec", duration / 100);

    dijkstra(1);
    for(int i=0;i<numNodes;i++){
        printf("%d\n",distances[i]);
    }

    return 0;
}