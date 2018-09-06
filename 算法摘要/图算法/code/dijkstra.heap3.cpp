
/*
    dijkstra algorithm
    no structure
    1. graph: adj list, use vector
    2. use min heap.
    3. no malloc

    please use luogu p4779 test examples
    O2 优化后 ： 270ms，与 queue1 版本差不多。
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> adj;

const int MAX_N = 100000;
const int INF = 0x7fffffff;

vector<adj> adjs[MAX_N];
int size;
int heap[MAX_N];
int keys[MAX_N];
int values[MAX_N];

void add_edge(int u, int v, int weight)
{
    adjs[u].push_back(make_pair(v, weight));
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
    int i, j, spe;
    init_heap(n, INF);
    decrease_key(src, 0);

    while (!empty_heap())
    {
        extract_min(i, spe);
        dist[i] = spe;
        vector<adj>::iterator it;
        for (it = adjs[i].begin(); it != adjs[i].end(); ++it)
        {
            j = it->first;
            if (dist[i] + it->second < values[j])
                decrease_key(j, dist[i] + it->second);
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
    dijkstra(src - 1, dist, n);

    for (i = 0; i < n; ++i)
        printf("%d ", dist[i]);

    return 0;
}