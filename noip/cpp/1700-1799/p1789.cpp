// P1789 【Mc生存】插火把
// https://www.luogu.org/problemnew/show/P1789

#include <iostream>
#include <cstdlib>

using namespace std;

#define MAX_N 1000


int main() {
    int n, m, k, i;
    int cx, cy, x, y;
    bool M[MAX_N][MAX_N] = { false };

    cin >> n >> m >> k;
    for (i = 0; i < m; i++)
    {
        cin >> cx >> cy;
        for (x = cx - 2; x <= cx + 2; x++)
            for (y = cy - 2; y <= cy + 2; y++)
                if ((abs(x - cx) + abs(y - cy) <= 2) && (x > 0 && x <= n && y > 0 && y <= n))
                    M[x][y] = true;
    }
    for (i = 0; i < k; i++)
    {
        cin >> cx >> cy;
        for (x = cx - 2; x <= cx + 2; x++)
            for (y = cy - 2; y <= cy + 2; y++)
                if (x > 0 && x <= n && y > 0 && y <= n)
                    M[x][y] = true;
    }

    int count = 0;
    for (x = 1; x <= n; ++x)
        for (y = 1; y <= n; ++y)
            if (!M[x][y]) count++;

    cout << count;
}