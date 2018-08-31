/*
ID: yesimim1
TASK: transform
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("transform.in", "r");
    FILE *fout = fopen ("transform.out", "w");

#include <fstream>
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
*/

#include <cstdio>

const int MAX_N = 11;
char a[MAX_N][MAX_N];
char b[MAX_N][MAX_N];

int n;

bool match_rotate_90()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[j][n - i - 1] != a[i][j]) return false;
    return true;
}

bool match_rotate_180()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - i - 1][n - j - 1] != a[i][j]) return false;
    return true;
}

bool match_rotate_270()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - j - 1][i] != a[i][j]) return false;
    return true;
}

bool match_reflect()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][n - j - 1] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_90()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - j - 1][n - i - 1] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_180()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - i - 1][j] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_270()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[j][i] != a[i][j]) return false;
    return true;
}

bool match_origin()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] != a[i][j]) return false;
    return true;
}


int main()
{
    FILE *fin = fopen ("transform.in", "r");
    FILE *fout = fopen ("transform.out", "w");

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; ++i)
        fscanf(fin, "%s", a[i]);
    for (int i = 0; i < n; ++i)
        fscanf(fin, "%s", b[i]);
    
    if (match_rotate_90())
        fprintf(fout, "1");
    else if (match_rotate_180())
        fprintf(fout, "2");
    else if (match_rotate_270())
        fprintf(fout, "3");
    else if (match_reflect())
        fprintf(fout, "4");
    else if (match_reflect_rotate_90() || match_reflect_rotate_180() || match_reflect_rotate_270())
        fprintf(fout, "5");
    else if (match_origin())
        fprintf(fout, "6");
    else
        fprintf(fout, "7");
    
    fprintf(fout, "\n");
    
    return 0;
}