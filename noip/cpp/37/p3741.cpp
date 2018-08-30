// P3741 honoka的键盘
// https://www.luogu.org/problemnew/show/P3741

#include <cstdio>

#define MAX_N 101

int main()
{
    int n, i;
    char s[MAX_N];
    scanf("%d", &n);
    scanf("%s", s);
    int count = 0;
    for (i = 1; i < n; ++i)
        if (s[i - 1] == 'V' && s[i] == 'K')
        {
            s[i - 1] = s[i] = '#';
            count++;
            i++;   //  i + 2
        }
    for (i = 1; i < n; ++i)
        if ((s[i - 1] != '#' && s[i] == 'K')         // change i-1 -> V
            || (s[i - 1] == 'V' && s[i] != '#'))    // change i -> K
        {
            count++;
            break;
        }
    printf("%d", count);
}