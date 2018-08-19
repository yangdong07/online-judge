// P1996 约瑟夫问题
// https://www.luogu.org/problemnew/show/P1996

#include <iostream>

using namespace std;

int main()
{
    const int MAX_N = 101;

    int n, m;
    int killed[MAX_N] = { false };

    cin >> n >> m;

    int i = 0, j = 0;  // i for pointer, j for counter of alive
    for (int k = 0; k < n; ++k)
    {
        for (j = 0; ; ++i)
            if (!killed[i % n])
                if (++j == m) break;

        cout << (i % n) + 1 << " ";
        killed[i++ % n] = true;
    }
    return 0;
}