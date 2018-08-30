// P1146 硬币翻转
// https://www.luogu.org/problemnew/show/P1146

#include <cstdio>

using namespace std;

#define MAX_N 101

int main() 
{
    int n, i;
    char s0[MAX_N], s1[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i) 
    {
        s0[i] = '0';
        s1[i] = '1';
    }
    s0[n] = s1[n] = '\0';

    printf("%d", n);
    for (i = 0; i < n; ++i) 
    {
        s0[i] = '1';
        s1[i] = '0';
        if (i & 1) printf("\n%s", s0);
        else printf("\n%s", s1);
    }
}