/*
ID: yesimim1
TASK: combo
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("combo.in", "r");
    FILE *fout = fopen ("combo.out", "w");

#include <fstream>
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");
*/

#include <cstdio>

int n;

bool near(int a, int b)
{
    if (a < b)
        return (b - a) <= 2 || (a + n - b) <= 2;
    else
        return (a - b) <= 2 || (b + n - a) <= 2;
}

bool valid(int a, int b, int c, int code[])
{
    return near(a, code[0]) && near(b, code[1]) && near(c, code[2]);
}


int main()
{
    FILE *fin = fopen ("combo.in", "r");
    FILE *fout = fopen ("combo.out", "w");

    fscanf(fin, "%d", &n);

    int i, j, k;
    int a[3], b[3];
    for (i = 0; i < 3; ++i)
        fscanf(fin, "%d", a + i);
    for (i = 0; i < 3; ++i)
        fscanf(fin, "%d", b + i);

    int count = 0;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            for (k = 1; k <= n; ++k)
                if (valid(i, j, k, a) || valid(i, j, k, b))
                    count++;
    fprintf(fout, "%d\n", count);

    return 0;
}