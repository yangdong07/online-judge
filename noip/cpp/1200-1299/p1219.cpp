// P1219 八皇后
// https://www.luogu.org/problemnew/show/P1219

#include <iostream>

using namespace std;

int q[100], p[100], x1[100], x2[100];
// q 皇后在每一行的位置， q[i] = j 表示位于 第 i 行 第 j 列。
// p 皇后已经占领的列， p[j] = 1 表示 j 列被占领。
// x1 皇后已经占领的主对角线, 在每条对角线上， j - i 是相同的， 所以 x1[j - i + n] 表示 j - i 对角线被占领。
// x2 皇后已经占领的副对角线, 在每条斜对角线上， j + i 是相同的， 所以 x2[i + j] 表示 j - i 是否被占领。

int n;     // 棋盘大小 n * n;
int s = 0;     // 解的数量

void print_queen()
{
    for (int i = 0; i < n; i++)
        cout << q[i] + 1 << " ";
    cout << endl;
}

void queen_search(int i) 
{
    if (i == n)
    {
        s++;
        if (s <= 3)
            print_queen();
        return;
    }
    else
    {
        for (int j = 0; j < n; j++)
        {
            if (!p[j] && !x1[j - i + n] && !x2[i + j])
            {
                q[i] = j;
                p[j] = x1[j - i + n] = x2[i + j] = 1;
                queen_search(i + 1);
                p[j] = x1[j - i + n] = x2[i + j] = 0;
            }
        }
    }
}

int main()
{
    cin >> n;      
    queen_search(0);
    cout << s; 
    return 0;
}