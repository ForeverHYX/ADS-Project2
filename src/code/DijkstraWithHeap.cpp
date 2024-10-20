#include <iostream> // for std::cin, std::cout
#include <vector>   // for std::vector
#include <cstdio>   // for std::scanf, std::printf
#include <limits>   // for std::numeric_limits
#include "Heap.hpp" // Include your Heap header

const int MaxN = 100010, MaxM = 500010;

struct edge {
    int to, dis, next;
};

edge e[MaxM];
int head[MaxN], dis[MaxN], cnt;
bool vis[MaxN];
int n, m, s;

inline void add_edge(int u, int v, int d) {
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

// 在 Heap.hpp 中定义 node，因此这里不再重复定义
// struct node {
//     int dis;
//     int pos;
// 
//     // 只重载 > 运算符用于最小堆比较
//     bool operator >(const node &other) const {
//         return dis > other.dis; // For min-heap
//     }
// };

Heap<node> q;

inline void dijkstra() {
    dis[s] = 0;
    q.insert((node){0, s});
    
    while (!q.heap.empty()) {
        node tmp = q.find_min();
        q.delete_min();
        
        int x = tmp.pos, d = tmp.dis;
        if (vis[x])
            continue;

        vis[x] = true;

        for (int i = head[x]; i; i = e[i].next) {
            int y = e[i].to;
            if (dis[y] > dis[x] + e[i].dis) {
                dis[y] = dis[x] + e[i].dis;
                if (!vis[y]) {
                    q.insert((node){dis[y], y});
                }
            }
        }
    }
}

int main() {
    std::scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; ++i) dis[i] = std::numeric_limits<int>::max(); // Initialize distances
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        std::scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
        std::printf("%d ", dis[i]);
    return 0;
}
