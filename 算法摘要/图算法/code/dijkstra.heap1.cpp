
/*
    dijkstra algorithm
    1. graph: adj list, use vector
    2. use min heap.
    3. dynamic allocate memory.

    please use luogu p4779 test examples
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> adj;

const int INF = 0x7fffffff;

struct Graph
{
    int n;  // number of vertices
    vector<adj> *adjs;
    Graph(int n): n(n)
    {
        adjs = (vector<adj>*) calloc(n, sizeof(vector<adj>));
    }

    void add_edge(int u, int v, int weight)
    {
        adjs[u].push_back(make_pair(v, weight));
        // adjs[v].push_back(make_pair(u, weight));
    }

};


struct MinHeap
{
    int size;
    int capacity;
    int *heap;   // [keys]
    int *keys;   // [heap index]
    int *values; // shortest path estimate, int? T?

    MinHeap(int n): size(n), capacity(n)
    {
        heap = (int *)calloc(n, sizeof(int));
        keys = (int *)calloc(n, sizeof(int));
        values = (int *)calloc(n, sizeof(int));
    }

    void _swap(int i1, int i2)
    {
        // swap in heap
        int k1 = heap[i1], k2 = heap[i2];
        heap[i1] = k2; heap[i2] = k1;
        keys[k1] = i2; keys[k2] = i1;
    }

    bool empty() { return size == 0; }

    void init(int value)
    {
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
            j = (i - 1) / 2;  // parent node
            if (values[heap[i]] < values[heap[j]])
                _swap(i, j);
            else
                break;
            i = j;
        }
    }
    
    // void print_heap()
    // {
    //     for (int i = 0; i < size; ++i)
    //         printf("%-5d", heap[i]);
    //     printf("\n");
    //     for (int i = 0; i < size; ++i)
    //     {
    //         if (values[heap[i]] != INF)
    //             printf("%-5d", values[heap[i]]);
    //         else
    //             printf("%-5s", "INF");
    //     }
    //     printf("\n");
    // }
};


void dijkstra(Graph &g, int src, int dist[])
{
    int n = g.n, i, j, spe;

    MinHeap min_heap = MinHeap(n);
    min_heap.init(INF);
    min_heap.decrease_key(src, 0);

    while (!min_heap.empty())
    {
        min_heap.extract_min(i, spe);
        dist[i] = spe;
        // relax edges
        vector<adj>::iterator it;
        for (it = g.adjs[i].begin(); it != g.adjs[i].end(); ++it)
        {
            j = it->first;
            spe = min_heap.values[j];  
            if (dist[i] + it->second < min_heap.values[j])
                min_heap.decrease_key(j, dist[i] + it->second);
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

    Graph g = Graph(n);

    for (k = 0; k < m; ++k)
    {
        read_num(i);
        read_num(j);
        read_num(weight);
        g.add_edge(i - 1, j - 1, weight);
    }

    int *dist = (int *)malloc(n * sizeof(int));
    dijkstra(g, src - 1, dist);

    for (i = 0; i < n; ++i)
        printf("%d ", dist[i]);

    return 0;
}