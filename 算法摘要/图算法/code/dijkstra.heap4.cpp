
/*
    dijkstra algorithm
    no vector
    1. graph: edges, use array list
    2. vertices: shortest path estimate
    3. use min heap

    please use luogu p4779 test examples
    优化前： 286ms， O2优化后 180ms
*/

#include <cstdio>
#include <queue>

using namespace std;

const int INF = 0x7fffffff;
const int MAX_V = 100000;
const int MAX_E = 200000;

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

int size;
int heap[MAX_V];
int keys[MAX_V];
int values[MAX_V];

edge edges[MAX_E + 1];
int head[MAX_V] = {0}, ec = 0;

void add_edge(int u, int v, int w)
{
    edges[++ec].v = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec;
}

void _swap(int i1, int i2)
{
    // swap in heap
    int k1 = heap[i1], k2 = heap[i2];
    heap[i1] = k2; heap[i2] = k1;
    keys[k1] = i2; keys[k2] = i1;
}

bool empty_heap() { return size == 0; }

void init_heap(int _size, int value)
{
    size = _size;
    for (int i = 0; i < size; ++i)
    {
        keys[i] = i;
        heap[i] = i;
        values[i] = value;
    }
}

void extract_min(int &key, int &value)
{
    key = heap[0];
    value = values[key];
    _swap(0, --size);

    // sink 0
    int i = 0, j;
    while (2 * i + 1 < size)
    {
        j = 2 * i + 1;
        if (j + 1 < size && values[heap[j]] > values[heap[j + 1]])
            ++j;
        if (values[heap[i]] > values[heap[j]])
            _swap(i, j);
        else
            break;
        i = j;
    }
}

void decrease_key(int key, int value)
{
    int i = keys[key], j;
    values[key] = value;

    while (i)
    {
        j = (i - 1) / 2; // parent node
        if (values[heap[i]] < values[heap[j]])
            _swap(i, j);
        else
            break;
        i = j;
    }
}

void dijkstra(int src, int dist[], int n)
{
    int i, j, k, spe;
    init_heap(n, INF);
    decrease_key(src, 0);

    while (!empty_heap())
    {
        extract_min(i, spe);
        dist[i] = spe;

        for (k = head[i]; k; k = edges[k].next)
        {
            j = edges[k].v;
            if (dist[i] + edges[k].w < values[j])
                decrease_key(j, dist[i] + edges[k].w);
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

    int dist[MAX_V];
    dijkstra(src - 1, dist, n);

    for (i = 0; i < n; ++i)
        printf("%d ", dist[i]);

    return 0;
}