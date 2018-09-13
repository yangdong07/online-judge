/*
ID: yesimim1
TASK: butter
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("butter.out");
    ifstream fin ("butter.in");
*/

#include <cstdio>
#include <queue>

using namespace std;

const int INF = 1450 * 255 * 800 + 1;
const int MAX_N = 500;
const int MAX_V = 800 + MAX_N + 1;
const int MAX_E = 1450 * 2 + MAX_N;

FILE *fin = fopen ("butter.in", "r");
FILE *fout = fopen ("butter.out", "w");

void _fputc(char c) { fputc(c, fout); }

struct edge 
{
    int v, w, next;
};

struct vertex 
{
    int v, d;
    vertex(int v, int d) : v(v), d(d) {}
    bool operator<(const vertex &b) const
    {
        return d > b.d;   // min first, max last
    }
};

edge edges[MAX_E + 1];
int head[MAX_V] = {0}, ec = 0;

void add_edge(int u, int v, int w)
{
    edges[++ec].v = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec;
}

void dijkstra(int src, int dist[], int n)
{
    int i, j, k, spe;
    for (i = 1; i <= n; ++i)
        dist[i] = INF;
    priority_queue<vertex> pq;

    dist[src] = 0;
    pq.push(vertex(src, 0));

    while (!pq.empty())
    {
        i = pq.top().v;
        spe = pq.top().d;
        pq.pop();
        if (spe > dist[i]) continue;
        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (dist[i] + edges[k].w < dist[j])
            {
                dist[j] = dist[i] + edges[k].w;
                pq.push(vertex(j, dist[j]));
            }
        }
    }
}

int main()
{
    int n, n_cows, m;
    fscanf(fin, "%d %d %d", &n_cows, &n, &m);

    // pasture start from 1 to n;
    // cows start from n + 1 to n + n_cows;
    int i, j, k, w;
    for (i = 1; i <= n_cows; ++i)
    {
        fscanf(fin, "%d", &j);
        add_edge(j, i + n, 0);
    }

    // n pasture edges
    for (k = 1; k <= m; ++k)
    {
        fscanf(fin, "%d %d %d", &i, &j, &w);
        add_edge(i, j, w);
        add_edge(j, i, w);
    }

    int dist[MAX_V], min_s = INF, sum;
    for (k = 1; k <= n; ++k)
    {
        dijkstra(k, dist, n + n_cows);
        sum = 0;
        for (i = n + 1; i <= n + n_cows; ++i)
            sum += dist[i];
        min_s = min(min_s, sum);
    }
    fprintf(fout, "%d\n", min_s);

    return 0;
}
