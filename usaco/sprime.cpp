/*
ID: yesimim1
TASK: sprime
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("sprime.in", "r");
    FILE *fout = fopen ("sprime.out", "w");

#include <fstream>
    ofstream fout ("sprime.out");
    ifstream fin ("sprime.in");
*/

#include <cstdio>

FILE *fin = fopen("sprime.in", "r");
FILE *fout = fopen("sprime.out", "w");
int depth;

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

void dfs(int n, int d)
{
    if (d == depth)
    {
        fprintf(fout, "%d\n", n);
        return;
    }

    n *= 10;
    for (int i = 1; i < 10; i += 2)
        if (is_prime(n + i)) dfs(n + i, d + 1);
}

int main()
{
    fscanf(fin, "%d", &depth);

    dfs(2, 1);
    dfs(3, 1);
    dfs(5, 1);
    dfs(7, 1);

    return 0;
}