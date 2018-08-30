// P1321 单词覆盖还原
// https://www.luogu.org/problemnew/show/P1321

#include <cstdio>
#include <cstring>

#define BUFFER_SIZE 256

int main()
{
    char s[BUFFER_SIZE];
    scanf("%s", s);
    int len = strlen(s);
    int boy = 0, girl = 0;

    for (int i = 0; i < len; ++i)
    {
        if (i < len - 2 && (s[i] == 'b' || s[i+1] == 'o' || s[i+2] == 'y')) boy++;
        if (i < len - 3 && (s[i] == 'g' || s[i+1] == 'i' || s[i+2] == 'r' || s[i+3] == 'l')) girl++;
    }
    printf("%d\n%d", boy, girl);
}