
// P3371 【模板】单源最短路径（弱化版）
// https://www.luogu.org/problemnew/show/P3371

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

typedef pair<int, int> adj;
typedef pair<int, int> kvp;   // key value pair

const int INF = 0x3f3f3f3f;

struct Graph
{
    int n;  // number of vertices
    vector<adj> *adjs;
    Graph(int n): n(n)
    {
        adjs = (vector<adj>*) calloc(n, sizeof(vector<adj>));
        // adjs = (vector<adj>*) malloc(n * sizeof(vector<adj>));
        // memset(adjs, 0, n * sizeof(vector<adj>));
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
    int *khi;  // index in heap
    int *heap; // heap of index/pointer
    kvp *kvs;  // key-values

    MinHeap(int n): size(n), capacity(n)
    {
        kvs = (kvp *)calloc(n, sizeof(kvp));
        heap = (int *)calloc(n, sizeof(int));
        khi = (int *)calloc(n, sizeof(int));
    }

    void swap_i(int i1, int i2)
    {
        int k1 = heap[i1], k2 = heap[i2];
        heap[i1] = k2; heap[i2] = k1;
        khi[k1] = i2; khi[k2] = i1;
    }

    void swap_k(int k1, int k2)
    {
        int i1 = khi[k1], i2 = khi[k2];
        heap[i1] = k2; heap[i2] = k1;
        khi[k1] = i2; khi[k2] = i1;
    }

    bool empty() { return size == 0; }

    void init_spe(int src)   // special init
    {
        for (int i = 0; i < size; ++i)
        {
            khi[i] = i;
            heap[i] = i;
            if (i == src)
                kvs[i] = make_pair(src, 0);
            else
                kvs[i] = make_pair(i, INF);
        }
        swap_k(0, src);
    }

    kvp extrac_min()
    {
        // printf("\n1. extract min\n");
        // print_heap();
        int index = heap[0];
        swap_i(0, --size);
        // printf("\n2. after extract\n");
        // print_heap();

        // sink 0
        int i = 0, j;
        while (2 * i + 1 < size)
        {
            j = 2 * i + 1;
            if (j + 1 < size && kvs[heap[j]].second > kvs[heap[j + 1]].second)
                ++j;
            if (kvs[heap[i]].second > kvs[heap[j]].second)
                swap_i(i, j);
            else
                break;
            i = j;
        }
        // printf("\n3. after sink\n");
        // print_heap();
        return kvs[index];
    }

    void decrease(int key, int value)
    {
        int i = khi[key], j;
        kvs[key].second = value;
        while (i)
        {
            j = (i - 1) / 2;  // parent node
            if (kvs[heap[i]].second < kvs[heap[j]].second)
                swap_i(i, j);
            else
                break;
            i = j;
        }
        // printf("\n4. decrease %d %d\n", key, value);
        // print_heap();
    }
    
    void print_heap()
    {
        for (int i = 0; i < size; ++i)
            printf("%-5d", heap[i]);
        printf("\n");
        for (int i = 0; i < size; ++i)
        {
            if (kvs[heap[i]].second != INF)
                printf("%-5d", kvs[heap[i]].second);
            else
                printf("%-5s", "INF");
        }
        printf("\n");
    }

};


void dijkstra(Graph &g, int src, int dist[])
{
    int n = g.n, i, j, weight, sp;
    MinHeap min_heap = MinHeap(n);
    min_heap.init_spe(src);

    while (!min_heap.empty())
    {
        kvp kv = min_heap.extrac_min();
        i = kv.first;
        dist[i] = kv.second;

        vector<adj>::iterator it;
        for (it = g.adjs[i].begin(); it != g.adjs[i].end(); ++it)
        {
            j = it->first;
            sp = min_heap.kvs[j].second;   // 
            if (dist[i] + it->second < min_heap.kvs[j].second)
            {
                min_heap.decrease(j, dist[i] + it->second);
            }
        }
    }

}

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int main()
{
    // create the graph given in above fugure
    int n, m, src;
    struct Graph g = Graph(9);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14);
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(7, 8, 7);

    // vector<adj>::iterator it;
    // for (int i = 0; i < g.n; ++i)
    // {
    //     printf("%lu\n", g.adjs[i].size());
    //     for (it = g.adjs[i].begin(); it != g.adjs[i].end(); ++it)
    //         printf("%d -> %d : %d\n", i, it->first, it->second);
    // }
    int dist[11];
    dijkstra(g, 0, dist);

    for (int i = 0; i < g.n; ++i)
        printf("%d %d\n", i, dist[i]);

    return 0;
}
