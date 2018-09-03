/*
ID: yesimim1
TASK: concom
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("concom.out");
    ifstream fin ("concom.in");
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

FILE *fin = fopen("concom.in", "r");
FILE *fout = fopen("concom.out", "w");

const int MAX_N = 101;
int n;
int holding[MAX_N][MAX_N] = {0};

// bfs like search
void search(int i, int hold[])
{
    queue<int> cq; // control queue;
    hold[i] = 100; // self control
    cq.push(i);    // self control

    while (!cq.empty())
    {
        int c = cq.front();
        cq.pop();
        for (int j = 1; j <= n; ++j)
        {
            if (hold[j] <= 50)
            {
                hold[j] += holding[c][j];
                if (hold[j] > 50)
                    cq.push(j);
            }
        }
    }
}

int main()
{
    int m, k;
    fscanf(fin, "%d", &m);
    int i, j, p;
    for (k = 0; k < m; ++k)
    {
        fscanf(fin, "%d%d%d", &i, &j, &p);
        holding[i][j] = p;
        n = max(n, max(i, j));
    }

    int hold[MAX_N];  // like visit mark array
    for (i = 1; i <= n; ++i)
    {
        memset(hold, 0, sizeof(hold));
        search(i, hold);
        for (j = 1; j <= n; ++j)
            if (i != j && hold[j] > 50) fprintf(fout, "%d %d\n", i, j);
    }

    return 0;
}