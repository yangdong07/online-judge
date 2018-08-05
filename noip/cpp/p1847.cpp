// P1847 轰炸II
// https://www.luogu.org/problemnew/show/P1847

#include <iostream>

using namespace std;

#define MAX_N 2001

int main()
{
    int m, n; // m 是轰炸数； n 是关键点数
    int i, j;
    long long a[MAX_N][4] = {0}; // 轰炸矩阵区域, x1, y1, x2, y2

    cin >> m >> n;

    for (i = 0; i < m; ++i)
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];

    long long px, py;
    int count, index;
    for (j = 0; j < n; ++j)
    {
        cin >> px >> py;

        count = 0;
        index = 0;

        for (i = 0; i < m; ++i)
        {
            if (px >= a[i][0] && px <= a[i][2] && py >= a[i][1] && py <= a[i][3])
            {
                count++;
                index = i + 1;
            }
        }
        if (index)
            cout << "YES " << count << " " << index << endl;
        else
            cout << "NO" << endl;
    }
}