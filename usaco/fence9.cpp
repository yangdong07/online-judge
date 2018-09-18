/*
ID: yesimim1
TASK: fence9
LANG: C++

#include <cstdio>
#include <fstream>
    ofstream fout ("fence9.out");
    ifstream fin ("fence9.in");
*/

#include <cstdio>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int main()
{
    FILE *fin = fopen("fence9.in", "r");
    FILE *fout = fopen("fence9.out", "w");

    int n, m, p;
    fscanf(fin, "%d%d%d", &n, &m, &p);

    int b;
    b = gcd(n, m) + gcd(m, p > n ? p - n : n - p) + p;
    fprintf(fout, "%d\n", p * m / 2 - b / 2 + 1);
    return 0;
}