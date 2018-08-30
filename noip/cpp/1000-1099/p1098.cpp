// P1098 字符串的展开
// https://www.luogu.org/problemnew/show/P1098

#include <cstdio>
#include <cstring>
#include <cctype>

#define MAX_N 20000

int mask(int c) { return '*'; }

bool can_expand(char *s, int n, int i)
{
    if (s[i] != '-')
        return false;
    if (i == 0 || i == n - 1)
        return false;
    if (s[i - 1] >= s[i + 1])
        return false;

    char a = s[i - 1], b = s[i + 1];
    if ((isdigit(a) && isdigit(b)) 
        || (isalpha(a) && isalpha(b)))
        return true;

    return false;
}

int expand(char *b, char a, char z, int p1, int p2, int p3)
{
    char c;
    const int repeat = p2;
    const int l = (z - a + 1) * repeat;

    // convert
    int (*convert)(int);
    if (p1 == 1)
        convert = &tolower;
    else if (p1 == 2)
        convert = &toupper;
    else
        convert = &mask;

    // write
    int i = 0, j;
    for (c = a; c <= z; ++c)
        for (j = 1; j <= repeat; ++j)
            b[i++] = convert(c);

    // reverse
    if (p3 == 2)
    {
        i = 0, j = l - 1;
        while (i < j)
        {
            c = b[i];
            b[i++] = b[j];
            b[j--] = c;
        }
    }

    return l;
}

int main()
{
    char s[200];
    char buffer[MAX_N];

    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    scanf("%s", s);

    int i, j = 0;  // pointer of s & buffer;
    int n = strlen(s);

    // j = expand(buffer, 'a', 'z', 3, 2, 2);
    // printf("%s\n", buffer);

    for (i = 0; i < n; ++i)
    {
        if (can_expand(s, n, i))
            j += expand(buffer + j, s[i - 1] + 1, s[i + 1] - 1, p1, p2, p3);
        else
            buffer[j++] = s[i];
    }
    buffer[j] = '\0';
    printf("%s", buffer);
}