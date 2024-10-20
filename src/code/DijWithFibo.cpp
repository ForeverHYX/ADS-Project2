#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <time.h>
#include "FibonacciHeap.hpp"

using namespace std;

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
            minHeap.insert({distances[y], y});
        }
    }
}

inline void dijkstra(int startNode)
{
    distances[startNode] = 0;
    minHeap.insert({0, startNode});

    while (minHeap.heap != nullptr)
    {
        auto current = minHeap.find_min();
        minHeap.delete_min();

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

clock_t start, stop;
double duration;
int main()
{
    int startnode,destination;
    double once_time;
    duration = 0;
    
    for (int k = 1; k <= 10; k++)
    {
        srand((unsigned int)time(0));
        FILE *file = fopen("SAMPLE.txt", "r");
        fscanf(file, "%d %d\n", &numNodes, &numEdges);
        for (int i = 1; i <= numNodes; ++i){
            distances[i] = numeric_limits<int>::max();
            head[i]=0;
            visited[i]=false;
        }
        edgeCount=0;
        for (int i = 0; i < numEdges; ++i)
        {
            char a;
            int u, v, d;
            fscanf(file, "%c %d %d %d\n", &a, &u, &v, &d);

            addEdge(u, v, d);
        }

        startnode = (rand()*k)%30000;
        startnode*=30000;
        startnode+=rand()%30000;
        startnode %= numNodes;
        startnode++;
        
        do {
        destination = (rand()*k)%30000;
        destination*=30000;
        destination+=rand()%30000;
        destination %= numNodes;
        destination++;
        }while(destination==startnode);
        

        start = clock();
        dijkstra(startnode);
        stop = clock();
        once_time = ((double)(stop - start)) / CLK_TCK;
        
        duration += once_time;

        printf("the length of shortest path from %d to %d is %d\n", startnode, destination, distances[destination]);
    }

    printf("this function costs average %lf sec", duration/100);

    return 0;
}