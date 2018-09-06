
/*
    dijkstra algorithm
    1. graph: adj list, use vector
    2. vertex: shortest path estimate, use priority_queue
    3. no malloc

    please use luogu p4779 test examples
    测试时间： 1096ms，用 vector 还是慢一些。
    O2优化之后： 274ms
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> adj;

const int MAX_N = 100000;
const int INF = 0x7fffffff;

vector<adj> adjs[MAX_N];

void add_edge(int u, int v, int weight)
{
    adjs[u].push_back(make_pair(v, weight));
}

struct vertex 
{
    int v;
    int spe; // shortest path estimate
    vertex(int v, int d) : v(v), spe(d) {}
    bool operator<(const vertex &b) const
    {
        return spe > b.spe;  // min first, max last
    }
};

void dijkstra(int src, int dist[])
{
    int i, j, spe;

    priority_queue<vertex> pq;

    dist[src] = 0;
    pq.push(vertex(src, 0));

    while (!pq.empty())
    {
        i = pq.top().v;
        spe = pq.top().spe;
        pq.pop();
        if (spe > dist[i]) continue;
        vector<adj>::iterator it;
        for (it = adjs[i].begin(); it != adjs[i].end(); ++it)
        {
            j = it->first;
            if (dist[i] + it->second < dist[j])
            {
                dist[j] = dist[i] + it->second;
                pq.push(vertex(j, dist[j]));
            }
        }
    }
}

void read_num(int &num)
{
    char c;
    num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}

int main()
{
    int n, m, src, i, j, k, weight;
    read_num(n);
    read_num(m);
    read_num(src);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        add_edge(i - 1, j - 1, weight);
    }

    int dist[MAX_N];
    for (i = 0; i < n; ++i)
        dist[i] = INF;
    dijkstra(src - 1, dist);

    for (i = 0; i < n; ++i)
        printf("%d ", dist[i]);

    return 0;
}