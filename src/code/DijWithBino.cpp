#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <random>
#include <chrono>
#include "HeapLibrary/BinomialHeap.hpp"

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

// 用于记录insert和delete_min的累计时间
double totalInsertTime = 0;
double totalDeleteMinTime = 0;
int insertCount = 0;
int deleteMinCount = 0;

inline void relax(int x, int y, int d)
{
    if (distances[y] > distances[x] + d)
    {
        distances[y] = distances[x] + d;
        if (!visited[y])
        {
            // 记录insert操作的时间
            auto start = chrono::high_resolution_clock::now();
            minHeap.insert({distances[y], y});
            auto stop = chrono::high_resolution_clock::now();
            totalInsertTime += chrono::duration<double>(stop - start).count();
            insertCount++;
        }
    }
}

inline void dijkstra(int startNode)
{
    distances[startNode] = 0;

    auto startInsert = chrono::high_resolution_clock::now();
    minHeap.insert({0, startNode});
    auto stopInsert = chrono::high_resolution_clock::now();
    totalInsertTime += chrono::duration<double>(stopInsert - startInsert).count();
    insertCount++;

    while (minHeap.root_node != nullptr)
    {
        
        auto startDelete = chrono::high_resolution_clock::now();
        auto current = minHeap.find_min(); // Find minimum distance node
        minHeap.delete_min();
        auto stopDelete = chrono::high_resolution_clock::now();
        totalDeleteMinTime += chrono::duration<double>(stopDelete - startDelete).count();
        deleteMinCount++;

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

            auto start = chrono::high_resolution_clock::now();
            dijkstra(startnode);
            auto stop = chrono::high_resolution_clock::now();
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

    printf("Total insertion time: %.6lf s, average insertion time: %.6lf ms\n", totalInsertTime, (totalInsertTime / insertCount) * 1000);
    printf("Total delete_min time: %.6lf s, average delete_min time: %.6lf ms\n", totalDeleteMinTime, (totalDeleteMinTime / deleteMinCount) * 1000);

    return 0;
}
