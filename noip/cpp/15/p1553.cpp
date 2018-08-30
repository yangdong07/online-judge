// P1553 数字反转（升级版）
// https://www.luogu.org/problemnew/show/P1553

#include <cstdio>
#include <cstring>
#include <cctype>

void reverse_print(char *s, int n)
{
    // trail zeros
    int i = 0, j = n - 1;
    while (s[i] == '0') ++i;
    while (s[j] == '0') --j;

    if (i > j)
        putchar('0');
    else
        while (i <= j)
            putchar(s[j--]);

}

int main()
{
    char s[50];

    scanf("%s", s);

    int i;  // for string
    int j;  // for digits

    for (i = 0, j = 0; i < strlen(s); ++i)
    {
        if (isdigit(s[i]))
            ++j;
        else
        {
            if (j) reverse_print(&s[i-j], j);
            j = 0;
            putchar(s[i]);
        }
    }
    if (j)
        reverse_print(&s[i - j], j);
}
