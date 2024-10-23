#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <time.h>
#include <random>
#include <chrono>
#include "FibonacciHeap.hpp"

using namespace std;
using namespace chrono;

const int MAX_NODES = 25000000;
const int MAX_EDGES = 60000000;

struct Edge
{
    int to, distance, next;
};

Edge edges[MAX_EDGES];
int head[MAX_NODES], distances[MAX_NODES], edgeCount;
bool visited[MAX_NODES];
int numNodes, numEdges;

double total_insert_time = 0.0;
double total_deletemin_time = 0.0;
int insert_count = 0;
int deletemin_count = 0;

inline void addEdge(int u, int v, int d)
{
    edgeCount++;
    edges[edgeCount].distance = d;
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount;
}

FibonacciHeap<pair<int, int>> minHeap;

inline void relax(int x, int y, int d)
{
    if (distances[y] > distances[x] + d)
    {
        distances[y] = distances[x] + d;
        if (!visited[y])
        {
            auto start = high_resolution_clock::now();
            minHeap.insert({distances[y], y});
            auto stop = high_resolution_clock::now();
            total_insert_time += duration<double>(stop - start).count();
            insert_count++;
        }
    }
}

inline void dijkstra(int startNode)
{
    distances[startNode] = 0;
    auto start = high_resolution_clock::now();
    minHeap.insert({0, startNode});
    auto stop = high_resolution_clock::now();
    total_insert_time += duration<double>(stop - start).count();
    insert_count++;

    while (minHeap.heap != nullptr)
    {
        start = high_resolution_clock::now();
        auto current = minHeap.find_min();
        minHeap.delete_min();
        stop = high_resolution_clock::now();
        total_deletemin_time += duration<double>(stop - start).count();
        deletemin_count++;

        int x = current.second;
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

double total_duration;
int main()
{
    srand((unsigned int)time(0));
    int startnode, destination;
    double once_time;
    total_duration = 0;
    int times = 0;
    for (int cnt = 1; cnt <= 1; cnt++)
    {
        string filename = "FLA.txt"; 
        for (int k = 1; k <= 10; k++)
        {

            FILE *file = fopen(filename.c_str(), "r");
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

            startnode = dis(gen);
            do
            {
                destination = dis(gen);
            } while (destination == startnode);

            auto start = high_resolution_clock::now();
            dijkstra(startnode);
            auto stop = high_resolution_clock::now();
            once_time = chrono::duration<double>(stop - start).count();

            total_duration += once_time;
            times++;

            printf("the length of shortest path from %d to %d is %d, cost %.6lf ms\n", startnode, destination, distances[destination], once_time * 1000);
        }
    }

    double average_time = total_duration / times;

    if (average_time >= 1.0)
    {
        printf("this function costs average %.6lf s\n", average_time);
    }
    else
    {
        printf("this function costs average %.6lf ms\n", average_time * 1000);
    }

    printf("Total insertion time: %.6lf s, average insertion time: %.6lf ms\n", total_insert_time, (total_insert_time / insert_count) * 1000);
    printf("Total delete_min time: %.6lf s, average delete_min time: %.6lf ms\n", total_deletemin_time, (total_deletemin_time / deletemin_count) * 1000);

    return 0;
}
