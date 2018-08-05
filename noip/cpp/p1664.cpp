// P1664 每日打卡心情好
// https://www.luogu.org/problemnew/show/P1664

#include <iostream>

using namespace std;

int day_score(int continues)
{
    if (continues < 3)
        return 1;
    else if (continues < 7)
        return 2;
    else if (continues < 30)
        return 3;
    else if (continues < 120)
        return 4;
    else if (continues < 365)
        return 5;
    else
        return 6;
}

int main()
{
    int n, i;
    cin >> n;

    int sign, score = 0;
    int continues = 0;
    int breaks = 0;

    for (i = 0; i < n; ++i)
    {
        cin >> sign;
        if (sign)
        {
            continues -= (breaks ? 1 << (breaks - 1) : 0);
            if (continues < 0) continues = 0;
            score += day_score(++continues);
            breaks = 0;
        }
        else breaks++;
    }
    cout << score;
}
