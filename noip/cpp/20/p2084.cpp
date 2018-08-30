// P2084 进制转换
// https://www.luogu.org/problemnew/show/P2084

#include <cstdio>
#include <cstring>

#define MAX_N 1001

int main()
{
    int m, n, i;
    char s[MAX_N];
    scanf("%d %s", &m, s);

    n = strlen(s);

    i = 0;
    while (s[i] == '0') ++i;
    printf("%c*%d^%d", s[i], m, n - i - 1);
    for (++i; i < n; ++i)
        if (s[i] != '0')
            printf("+%c*%d^%d", s[i], m, n - i - 1);
    
}