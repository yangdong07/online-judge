// P2708 硬币翻转
// https://www.luogu.org/problemnew/show/P2708

#include <cstdio>
#include <cstring>

#define MAX_SIZE 65535

int main()
{
    char s[MAX_SIZE];
    scanf("%s", s);
    int i, len = strlen(s);
    int flips = 0;
    for (i = len - 1; i >= 0; --i)
        if ((s[i] - '0') ^ ((flips & 1) == 0))
            flips++;
    printf("%d", flips);
}