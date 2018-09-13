/*
ID: yesimim1
TASK: ratios
LANG: C++

#include <cstdio>

void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("ratios.out");
    ifstream fin ("ratios.in");
*/

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;


const double eps = 1e-10;
const int N = 3;   // num of unknown
const int MAX_X = 100;   // 

FILE *fin = fopen ("ratios.in", "r");
FILE *fout = fopen ("ratios.out", "w");

bool is_zero(double x)
{
    return fabs(x) < eps;
}

bool is_integer(double x)
{
    return fabs(x - round(x)) < eps;
}

bool constraint(double x)
{
    double y = round(x);
    return fabs(x - y) < eps && (int)y >= 0 && (int)y <= MAX_X;
}

void print_mat(double mat[N][N + 1])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N + 1; ++j)
            fprintf(fout, "%-6.2lf ", mat[i][j]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
}

bool gaussian_elimination(double mat[N][N + 1])
{
    int i, j, ii;
    double pivot;

    for (i = 0; i < N; ++i)
    {
        // find pivot, abs max
        int i_max = i;
        pivot = mat[i][i];
        for (ii = i + 1; ii < N; ++ii)
            if (fabs(mat[ii][i]) > fabs(pivot))
                i_max = ii, pivot = mat[ii][i];
        // if pivot is zero, the matrix is singular, return false
        if (is_zero(pivot))
            return false;
        
        // print_mat(mat);
        // swap rows, make pivot to mat[i][i]
        for (j = i; j < N + 1; ++j)
            swap(mat[i][j], mat[i_max][j]);
        for (j = i; j < N + 1; ++j)
            mat[i][j] /= pivot;

        // eliminate columns, for each row, eliminate factor = mat[ii][i] / mat[i][i] = mat[ii][i]
        for (ii = 0; ii < N; ++ii)
            if (ii != i)
            {
                double factor = mat[ii][i];
                for (j = i; j < N + 1; ++j)
                    mat[ii][j] -= mat[i][j] * factor;
            }
    }
    return true;
}

int main()
{
    int i, j, k;
    double a[N][N], b[N], x[N];   // ax = b

    for (i = 0; i < N; ++i)
        fscanf(fin, "%lf", &b[i]);

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            fscanf(fin, "%lf", &a[j][i]);
    
    double mat[N][N + 1];

    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
            mat[i][j] = a[i][j];
        mat[i][N] = b[i];
    }

    if (!gaussian_elimination(mat))
    {
        fprintf(fout, "NONE\n"); 
        return 0;
    }
    for (i = 0; i < N; ++i)
        x[i] = mat[i][N];
    
    // print_mat(mat);

    for (k = 1; k <= 100; k++)
    {
        // for (i = 0; i < N; ++i)
        //     fprintf(fout, "%d ", (int)round(x[i] * k));
        // fprintf(fout, "\n");

        for (i = 0; i < N; ++i)
            if (!constraint(x[i] * k))
                break;
        if (i == N)  // solution found
        {
            for (j = 0; j < N; ++j)
                fprintf(fout, "%d ", (int)round(x[j] * k));
            fprintf(fout, "%d\n", k);
            return 0;
        }
    }
    fprintf(fout, "NONE\n");
    return 0;
}