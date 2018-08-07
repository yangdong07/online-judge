// P1598 垂直柱状图
// https://www.luogu.org/problemnew/show/P1598


#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

#define ALPHA_NUM 26

// put n char in s, remove end space
void print(char *s, int n)
{
    int i, j = n - 1;
    while (j >= 0 && s[j] == ' ') --j;
    for (int i = 0; i <= j; ++i)
        putchar(s[i]);
    putchar('\n');
}

int main()
{
    int hist[ALPHA_NUM] = { 0 };
    char s[ALPHA_NUM * 2];
    char c;

    while ((c = getchar()) != EOF)
        if (isalpha(c))
            hist[toupper(c) - 'A'] += 1;
    
    int i, j, h;
    int max_height = 0;
    for (i = 0; i < ALPHA_NUM; ++i)
    {
        // printf("%d ", hist[i]);
        max_height = max(max_height, hist[i]);
    }

    for (h = max_height; h > 0; --h)
    {
        for (i = 0, j = 0; i < ALPHA_NUM; ++i)
        {
            s[j++] = hist[i] >= h ? '*' : ' ';
            s[j++] = ' ';
        }
        print(s, j);
    }
    for (i = 0, j = 0; i < ALPHA_NUM; ++i)
    {
        s[j++] = 'A' + i;
        s[j++] = ' ';
    }
    print(s, j);
}