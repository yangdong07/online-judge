// P1026 统计单词个数
// https://www.luogu.org/problemnew/show/P1026

#include <cstdio>
#include <cstring>

int min(int a, int b) { return a < b ? a : b; }

void read_abc(char s[], int n)
{
    char c;
    for (int i = 0; i < n;)
    {
        c = getchar();
        if (c >= 'a' && c <= 'z') s[i++] = c;
    }
    s[n] = '\0';
}

bool strcmp1(char *s1, char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *s2 == '\0';
}

bool strcmp2(char *s1, char *s2, int i1, int i2)
{
    // reverse compare
    while (i1 >= 0 && i2 >=0 && s1[i1] == s2[i2]) { --i1; --i2; }
    return i2 < 0;
}

int main()
{
    const int MAX_N = 200;
    const int MAX_W = 6;
    char s[MAX_N];
    char dict[MAX_W][MAX_N];
    int wl[MAX_W];

    int lines, k, i, j;
    scanf("%d", &lines);

    int len = lines * 20;
    read_abc(s, len);

    scanf("%d", &k);
    for (i = 0; i < k; ++i)
    {
        scanf("%s", dict[i]);
        wl[i] = strlen(dict[i]);
    }

    int wc[MAX_N][MAX_N] = {0};
    
    for (i = 0; i < len; ++i)
        for (j = 0)
        for (j = 0; j < k; ++j)
        {
            if (strncmp(s + i, dict[j], wl[j]) == 0)
            {
                wc1[i] = 1;
                wc2[i + wl[j] - 1] = 1;
            }
        }
    

    for (i = 1; i < len; ++i)
        wc1[i] += wc1[i - 1];
    for (i = len - 2; i >= 0; --i)
        wc2[i] += wc2[i + 1];

    for (i = 0; i < len; ++i)
        printf("%c ", s[i]);
    printf("\n");
    for (i = 0; i < len; ++i)
        printf("%d ", wc1[i]);
    printf("\n");
    for (i = 0; i < len; ++i)
        printf("%d ", wc2[i]);
    printf("\n");

    for (i = 1; i < len - 1; ++i)
        for (j = i; j < len - 1; ++j)
        {
            for (int k = i; k <= j; ++k) putchar(s[k]);
            printf(" %d\n", min(wc1[j] - wc1[i - 1], wc2[i] - wc2[j + 1]));
        }
    

    // printf("%s", s);


    return 0;
}