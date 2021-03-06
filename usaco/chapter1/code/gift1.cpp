/*
ID: yesimim1
TASK: gift1
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("gift1.in", "r");
    FILE *fout = fopen ("gift1.out", "w");
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    const int MAX_N = 12;
    map<string, int> balance;
    int n, i;
    string name;
    string names[MAX_N];

    fin >> n;
    for (i = 0; i < n; ++i)
    {
        fin >> name;
        balance[name] = 0;
        names[i] = name;
    }

    int given, m, j, average;
    for (i = 0; i < n; ++i)
    {
        fin >> name >> given >> m;
        average = m > 0 ? given / m : 0;
        balance[name] -= average * m;

        for (j = 0; j < m; ++j)
        {
            fin >> name;
            balance[name] += average;
        }
    }

    for (i = 0; i < n; ++i)
        fout << names[i] << " " << balance[names[i]] << endl;

    return 0;
}