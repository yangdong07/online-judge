/*
ID: yesimim1
TASK: hamming
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("hamming.out");
    ifstream fin ("hamming.in");
*/

#include <cstdio>

FILE *fin = fopen("hamming.in", "r");
FILE *fout = fopen("hamming.out", "w");

int hanmming_distance(int x, int y)
{
    int d = 0;
    for (int t = x ^ y; t; t >>= 1)
        if (t & 1) ++d;
    return d;
}

const int MAX_N = 65;

int N, B, D;
int codewords[MAX_N];

void print_codewords()
{
    for (int i = 1; i <= N; ++i)
    {
        fprintf(fout, "%d", codewords[i - 1]);
        fprintf(fout, i % 10 == 0 || i == N ? "\n" : " ");
    }
}

bool dfs(int code, int n)
{
    for (int i = 0; i < n; ++i)
        if (hanmming_distance(codewords[i], code) < D)
            return false;
    
    codewords[n] = code;
    if (n == N - 1)
    {
        print_codewords();
        return true;
    }

    for (int c = code + 1; c < (1 << B); ++c)
        if (dfs(c, n + 1)) return true;
    return false;
}

int main()
{
    fscanf(fin, "%d %d %d", &N, &B, &D);

    dfs(0, 0);
    
    return 0;
}