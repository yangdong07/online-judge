// P4327 [COCI2006-2007#1] Okviri
// https://www.luogu.org/problemnew/show/P4327

#include <cstdio>
#include <cstring>

#define MAX_N 20

void printLine1(int n)
{
    // n: num of characters
    for (int i = 1; i <= n; ++i)
        printf("..%c.", i % 3 == 0 ? '*': '#');
    printf(".\n");
}

void printLine2(int n)
{
    // n: num of characters
    char c;
    for (int i = 1; i <= n; ++i)
    {
        c = i % 3 == 0 ? '*' : '#';
        printf(".%c.%c", c, c);
    }
    printf(".\n");
}

void printMainLine(const char s[], int n)
{
    char c;
    putchar('#');
    for (int i = 0; i < n; ++i)
    {
        c = (i % 3 == 0 || (i % 3 == 1 && i == n - 1)) ? '#' : '*';
        printf(".%c.%c", s[i], c);
    }
    putchar('\n');
}

void printFrame(const char s[])
{
    int l = strlen(s);
    printLine1(l);
    printLine2(l);
    printMainLine(s, l);
    printLine2(l);
    printLine1(l);
    // printf("");
}


int main()
{
    char s[MAX_N];
    scanf("%s", s);
    printFrame(s);
    // printFrame("ABCDEFGHIJKLMNOPQRSTUVW");
    // printFrame("A");
    // printFrame("AB");
    // printFrame("ABC");
}