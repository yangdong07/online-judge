/*
ID: yesimim1
TASK: wormhole
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");
*/

#include <cstdio>
#include <algorithm>

struct Wormhole
{
    int x, y;
};

bool cmp(Wormhole &a, Wormhole &b)
{
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}

const int MAX_N = 13;
int n;
int next[MAX_N], wp[MAX_N];  // wp : warmhole pair map

int total = 0;


bool cycle()
{
    int i, p[MAX_N];
    for (i = 1; i <= n; ++i)
        p[i] = i;
    
    int step;
    for (i = 1; i <= n; ++i)
    {
        for (step = 0; step < n; ++step)
            p[i] = next[wp[p[i]]];
        
        if (p[i]) return true;
    }

    // for (i = 1; i <= n; ++i)
    //     fprintf(fout, "%d ", p[i]);
    // fprintf(fout, "\n");
    
    // for (i = 1; i <= n; ++i)
    //     if (p[i]) return true;
    return false;
}


// search pairs
void dfs(int i)
{
    if (i == n)
    {
        if (cycle()) total++;
        // for (i = 1; i <= n; ++i)
        //     fprintf(fout, "%d ", i);
        // fprintf(fout, "\n");
        // for (i = 1; i <= n; ++i)
        //     fprintf(fout, "%d ", wp[i]);
        // fprintf(fout, "\n");
    }
    if (wp[i])
        dfs(i + 1);
    else
        for (int j = 1; j <= n; ++j)
        {
            if (j != i && !wp[j])
            {
                wp[i] = j;
                wp[j] = i;
                dfs(i + 1);
                wp[i] = wp[j] = 0;
            }
        }
}

int main()
{
    FILE *fin = fopen ("wormhole.in", "r");
    FILE *fout = fopen ("wormhole.out", "w");

    int i;
    fscanf(fin, "%d", &n);
    Wormhole holes[MAX_N];

    for (i = 1; i <= n; ++i)
        fscanf(fin, "%d %d", &holes[i].x, &holes[i].y);
    
    std::sort(holes + 1, holes + 1 + n, cmp);

    for (i = 1; i < n; ++i)
        if (holes[i].y == holes[i + 1].y)
            next[i] = i + 1;
        else
            next[i] = 0;
    next[0] = next[i] = 0;   // last to 0;

    // for (i = 1; i <= n; ++i)
    // {
    //     fprintf(fout, "(%d %d) ", holes[i].x, holes[i].y);
    //     if (holes[i].y != holes[i + 1].y)
    //         fprintf(fout, "\n");
    // }

    // for (i = 1; i <= n + 1; ++i)
    //     fprintf(fout, "%d ", holes[i].y);
    // fprintf(fout, "\n");
    
    // for (i = 1; i <= n; ++i)
    //     fprintf(fout, "%d ", next[i]);
    // fprintf(fout, "\n");

    for (i = 1; i <= n; ++i)
        wp[i] = 0;

    total = 0;
    dfs(1);
    fprintf(fout, "%d\n", total);

    return 0;
}