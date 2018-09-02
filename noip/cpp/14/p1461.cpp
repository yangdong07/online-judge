
// P1461 海明码 Hamming Codes
// https://www.luogu.org/problemnew/show/P1461

#include <cstdio>

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
        printf("%d", codewords[i - 1]);
        printf(i % 10 == 0 || i == N ? "\n" : " ");
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
    scanf("%d %d %d", &N, &B, &D);

    dfs(0, 0);
    
    return 0;
}