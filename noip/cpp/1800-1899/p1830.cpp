// P1830 轰炸III
// https://www.luogu.org/problemnew/show/P1830

#include <iostream>

using namespace std;

#define MAX_N 100

int main()
{
    int n, m, x, y; // x 是轰炸数； y 是关键点数
    int i, j;
    int a[MAX_N][4] = {0}; // 轰炸矩阵区域, x1, y1, x2, y2

    cin >> n >> m >> x >> y;

    for (i = 0; i < x; ++i)
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];

    int px, py;
    int count, index;
    for (j = 0; j < y; ++j)
    {
        cin >> px >> py;

        count = 0;
        index = 0;

        for (i = 0; i < x; ++i)
        {
            if (px >= a[i][0] && px <= a[i][2] && py >= a[i][1] && py <= a[i][3])
            {
                count++;
                index = i + 1;
            }
        }
        if (index)
            cout << "Y " << count << " " << index << endl;
        else
            cout << "N" << endl;
    }
}