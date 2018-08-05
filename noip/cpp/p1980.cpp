// P1980 计数问题
// https://www.luogu.org/problemnew/show/P1980

#include <iostream>

using namespace std;

int solve1(int n, int d)
{
    int t, count = 0;
    for (int i = 1; i <= n; ++i)
    {
        t = i;
        while (t)
        {
            if (t % 10 == d)
                ++count;
            t /= 10;
        }
    }
    return count;
}

int solve2(int n, int d)
{
    int t;
    int a, x, b;  //  `axb`, a left, x digit, b right
    int m;  // 1, 10, 100....
    int count = 0;

    for (t = n, m = 1; t; m *= 10, t /= 10)
    {
        a = t / 10;
        x = t % 10;
        b = n % m;

        count += (a - (d == 0)) * m;

        if (x > d)
            count += m;
        else if (x == d)
            count += (b + 1);
    }

    return count;
}

int main()
{
    int n, d;
    cin >> n >> d;

    cout << solve2(n, d) << endl;
}