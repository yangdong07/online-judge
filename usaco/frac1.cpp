/*
ID: yesimim1
TASK: frac1
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("frac1.in", "r");
    FILE *fout = fopen ("frac1.out", "w");

#include <fstream>
    ofstream fout ("frac1.out");
    ifstream fin ("frac1.in");
*/

#include <cstdio>
#include <algorithm>

FILE *fin = fopen("frac1.in", "r");
FILE *fout = fopen("frac1.out", "w");

const int MAX_N = 161;

struct Fraction
{
    int numerator, denominator;
    Fraction(): numerator(0), denominator(1) {}
    Fraction(int a, int b): numerator(a), denominator(b) {}
    bool operator<(const Fraction &rhs) const
    {
        return numerator * rhs.denominator < denominator * rhs.numerator;
    }
};

int main()
{
    Fraction fractions[MAX_N * MAX_N];

    int matrix[MAX_N][MAX_N] = {0};
    int n, i, j;
    fscanf(fin, "%d", &n);

    fractions[0] = Fraction(0, 1);
    fractions[1] = Fraction(1, 1);
    int z = 2;
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= n; ++j)
        {
            if (!matrix[i][j])
            {
                fractions[z++] = Fraction(i, j);
                matrix[i][j] = 1;
                for (int k = 2; i * k <= n && j * k <= n; ++k)
                    matrix[i * k][j * k] = -1;
            }
        }
    
    // fprintf(fout, "%d", fractions[1] < fractions[2]);
    std::sort(fractions, fractions + z);

    for (i = 0; i < z; ++i)
        fprintf(fout, "%d/%d\n", fractions[i].numerator, fractions[i].denominator);


    return 0;
}