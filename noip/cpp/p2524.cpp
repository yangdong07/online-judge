// P2524 Uim的情人节礼物·其之弐
// https://www.luogu.org/problemnew/show/P2524

#include <cstdio>

using namespace std;

#define MAX_N 12

int main()
{
    int n, i, d;
    char s[MAX_N];
    scanf("%d", &n);
    scanf("%s", s);

    int factorial[MAX_N];
    int used[MAX_N];

    factorial[0] = 1;
    for (i = 1; i <= n; ++i)
    {
        used[i] = 1;
        factorial[i] = factorial[i - 1] * i;
    }

    int index = 1, choice;
    for (i = 0; i < n; ++i)
    {
        d = s[i] - '0';
        choice = 0;
        for (int j = 1; j < d; ++j) choice += used[j];
        index += choice * factorial[n - i - 1];
        used[d] = 0;
    }
    printf("%d", index);
}