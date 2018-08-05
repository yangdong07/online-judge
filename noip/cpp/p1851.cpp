// P1851 好朋友
// https://www.luogu.org/problemnew/show/P1851

#include <iostream>

using namespace std;

#define MAX_N 30000

int FACTORS[MAX_N] = { 0 };

void init_factors()
{
    for (int i = 1; i < MAX_N; ++i)
        for (int j = i + i; j < MAX_N; j += i)
            FACTORS[j] += i;
}

int main()
{
    init_factors();

    int s;
    cin >> s;

    for (int i = s; ; ++i)
    {
        if (FACTORS[i] < MAX_N && FACTORS[i] != i && FACTORS[FACTORS[i]] == i)
        {
            cout << i << " " << FACTORS[i];
            return 0;
        }
    }
}