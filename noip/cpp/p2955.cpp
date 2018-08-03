// P2955 [USACO09OCT]奇数偶数Even? Odd?
// https://www.luogu.org/problemnew/show/P2955


#include <cstdio>
#include <cstring>

#define MAX_SIZE  100

int main()
{
    int n, i, len;
    char s[MAX_SIZE];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%s", s);
        len = strlen(s);
        printf((s[len - 1] - '0') & 1 ? "odd\n" : "even\n");
    }

}