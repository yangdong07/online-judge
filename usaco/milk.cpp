/*
ID: yesimim1
TASK: milk
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("milk.in", "r");
    FILE *fout = fopen ("milk.out", "w");

#include <fstream>
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
*/

#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct Object
{
    int price;  // 单价
    int supply; // 供应量
} milk[5002];

bool cmp(Object &a, Object &b)
{
    return a.price < b.price;
}

int main()
{
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

    int n, m, i;

    fin >> n >> m;

    for (i = 0; i < m; i++)
        fin >> milk[i].price >> milk[i].supply;

    sort(milk, milk + m, cmp);

    int need = n, cost = 0, supply;

    i = 0;
    while (need > 0)
    {
        supply = min(milk[i].supply, need);

        need -= supply;
        cost += supply * milk[i++].price;
    }
    fout << cost << endl;
}