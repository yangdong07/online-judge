// P1328 生活大爆炸版石头剪刀布
// https://www.luogu.org/problemnew/show/P1328


#include <iostream>

using namespace std;

const int MAX_N = 201;

int vs[5][5] = {
    {0, 0, 1, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0}};

int main()
{
    int n, na, nb;
    cin >> n >> na >> nb;

    int i;
    int a[MAX_N], b[MAX_N];
    for (i = 0; i < na; i++)
        cin >> a[i];
    for (i = 0; i < nb; i++)
        cin >> b[i];

    // simulation
    int cnta = 0, cntb = 0;
    for (i = 0; i < n; i++)
    {
        cnta += vs[a[i % na]][b[i % nb]];
        cntb += vs[b[i % nb]][a[i % na]];
    }
    cout << cnta << " " << cntb << endl;
    return 0;
}