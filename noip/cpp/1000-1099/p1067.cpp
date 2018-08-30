// P1067 多项式输出
// https://www.luogu.org/problemnew/show/P1067

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

#define MAX_N 101
#define MAX_S 65536

int main()
{
    int c[MAX_N];

    int n, i;
    cin >> n;
    for (i = 0; i <= n; ++i)
        cin >> c[i];

    // skip 0s
    char s[MAX_S];
    int j = 0; // offset for s

    for (i = 0; i < n; ++i)
    {
        if (c[i])
        {
            j += sprintf(s + j, "%+d", c[i]);
            if (c[i] == 1 || c[i] == -1) --j;   // remove 1
            s[j++] = 'x';
            if (i < n - 1)
                j += sprintf(s + j, "^%d", n - i);
        }
    }
    if (c[i]) sprintf(s + j, "%+d", c[i]);

    printf("%s", s + (s[0] == '+'));
}
