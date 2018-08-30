// P1149 火柴棒等式
// https://www.luogu.org/problemnew/show/P1149

#include <iostream>

using namespace std;

#define MAX_N 2222

int main()
{
    int n;
    cin >> n;
    n -= 4;  // '+' '=', 4 sticks

    int sticks[MAX_N] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

    for (int i = 10; i < MAX_N; ++i)
    {
        sticks[i] = sticks[i % 10] + sticks[i / 10];
        // printf("%d ", sticks[i]);
    }

    int count = 0;
    for (int i = 0; i <= 1111; ++i)
        if (n > sticks[i])
        {
            for (int j = 0; j < i; ++j)
            {
                if (n == sticks[i] + sticks[j] + sticks[i + j])
                {
                    count += 2;
                    // printf("%d + %d = %d\n", i, j, i + j);
                    // printf("%d + %d + %d\n", sticks(i), sticks(j), sticks(i + j));
                }
            }
            if (n == sticks[i] * 2 + sticks[i * 2]) count++;
        }

        
    cout << count;
}