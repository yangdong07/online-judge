/*
ID: yesimim1
TASK: comehome
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("comehome.out");
    ifstream fin ("comehome.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 26 * 2;
const int MAX_INT = 0x7fffffff;

FILE *fin = fopen("comehome.in", "r");
FILE *fout = fopen("comehome.out", "w");
int adj[MAX_N][MAX_N];

int c2i(char c)
{
    if ('a' <= c && c <= 'z')
        return c - 'a';
    else
    return c - 'A' + 26;
}

char i2c(int i)
{
    if (0 <= i && i < 26)
        return 'a' + i;
    return 'A' + i - 26;
}

int readline(char *s)
{
    int i = 0;
    for (char c = fgetc(fin); c != '\n' && c != EOF; c = fgetc(fin))
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int parseint(char *s)
{
    int n = 0;
    for (; *s; ++s)
        n = n * 10 + *s - '0';
    return n;
}


int min_distance(int dist[], bool visit[], int V)
{
    int min_s = MAX_INT, min_index;

    for (int v = 0; v < V; ++v)
        if (!visit[v] && dist[v] <= min_s)
            min_s = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src, int dist[], int V)
{
    bool visit[V];
    for (int i = 0; i < V; i++)
        dist[i] = MAX_INT, visit[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = min_distance(dist, visit, V);
        visit[u] = true;
        if (dist[u] == MAX_INT) continue;
        for (int v = 0; v < V; v++)
            if (!visit[v] && adj[u][v] != MAX_INT && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
    }
}

int main()
{
    int p, i, j;
    fscanf(fin, "%d\n", &p);
    for (i = 0; i < MAX_N; ++i)
    {
        for (j = 0; j < MAX_N; ++j)
            adj[i][j] = MAX_INT;
    }

    char s[10];
    int a, b, weight;
    for (i = 0; i < p; ++i)
    {
        readline(s);
        a = c2i(s[0]), b = c2i(s[2]);
        weight = parseint(&s[4]);
        // fprintf(fout, "%c %c %d\n", a, b, weight);
        adj[a][b] = adj[b][a] = min(adj[a][b], weight);
    }
    // for (i = 0; i < MAX_N; ++i)
    // {
    //     for (j = 0; j < MAX_N; ++j)
    //         if (adj[i][j] != MAX_INT) fprintf(fout, "%c %c %d\n", i2c(i), i2c(j), adj[i][j]);
    // }

    int start = c2i('Z');
    int dist[MAX_N];
    dijkstra(start, dist, MAX_N);

    int min_i, min_dist = MAX_INT;
    for (i = MAX_N / 2; i < MAX_N; ++i)
        if (i != start && dist[i] < min_dist)
            min_dist = dist[i], min_i = i;
    
    // for (i = 0; i < MAX_N; ++i)
    //     fprintf(fout, "%c %d\n", i2c(i), dist[i]);
    
    fprintf(fout, "%c %d\n", i2c(min_i), min_dist);
}