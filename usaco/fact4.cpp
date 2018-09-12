/*
ID: yesimim1
TASK: fact4
LANG: C++

#include <cstdio>

void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("fact4.out");
    ifstream fin ("fact4.in");
*/

#include <cstdio>

int main()
{
    FILE *fin = fopen("fact4.in", "r");
    FILE *fout = fopen("fact4.out", "w");

    int n, i;
    fscanf(fin, "%d", &n);

    // n = 9999;
    // n = 50000000;
    int _power8[] = {1, 8, 4, 2, 6};

    int ans = 1, n_eights = 0;
    while (n)
    {
        for (i = 1; i <= n % 5; ++i)
            ans *= i;
        n /= 5;
        if (n & 1) ans = (ans * 4) % 10;
        n_eights += n;
    }

    if (n_eights) ans *= _power8[(n_eights - 1) % 4 + 1];
    fprintf(fout, "%d\n", ans % 10);

    return 0;
}