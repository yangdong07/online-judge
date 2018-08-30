// P2705 小球
// https://www.luogu.org/problemnew/show/P2705

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int r, b, c, d, e;
    cin >> r >> b >> c >> d >> e;

    int score = r * c + b * d;
    if (2 * e > c + d)  // swtich as more as possible
        score += min(r, b) * (2 * e - c - d);
    cout << score;
}