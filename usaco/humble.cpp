/*
ID: yesimim1
TASK: humble
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("humble.out");
    ifstream fin ("humble.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_M = 100;
const int MAX_N = 100000 + 1;
const int INF = 0x7fffffff;

int humbles[MAX_N];
int primes[MAX_M];

int n, m;

int next_humble(int i)
{
    int l, r = i - 1, m;
    int min_h = INF;
    int last = humbles[i - 1], bound;

    for (int j = 0; j < m; ++j)
    {
        printf("%d %d\n", last, primes[j]);
        printf("%d %d\n", l, r);
        bound = last / primes[j];
        while (l < r)
        {
            m = (l + r) / 2;
            if (humbles[m] <= bound)
                l = m + 1;
            else
                r = m;
        }
        printf("%d\n", min_h);
        min_h = min(min_h, humbles[l] * primes[j]);
    }
    return min_h;
}

int main()
{
    FILE *fin = fopen ("humble.in", "r");
    FILE *fout = fopen ("humble.out", "w");

    int i, j;
    fscanf(fin, "%d %d", &m, &n);
    
    for (i = 0; i < m; ++i)
        fscanf(fin, "%d", &primes[i]);
    
    humbles[0] = 1;
    humbles[1] = primes[0];

    for (i = 2; i <= n; ++i)
        humbles[i] = next_humble(i);

    fprintf(fout, "%d\n", humbles[n]);

    return 0;
}