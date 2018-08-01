// P1307 数字反转
// https://www.luogu.org/problemnew/show/P1307

#include <cstdio>
#include <cstring>

#define MAX_SIZE 15

int main()
{
    char s[MAX_SIZE], c;
    scanf("%s", s);
    int i = 0, j, l = strlen(s);
    if (s[0] == '-') i = 1;

    // rstrip '0'
    while (s[--l] == '0');
    s[++l] = '\0';

    // reverse
    for (int k = 0; k < (l - i) / 2; ++k)
    {
        // swap s[i+k], s[j-k-1]
        c = s[l - k - 1];
        s[l - k - 1] = s[i + k];
        s[i + k] = c;
    }
    printf("%s", s);
}