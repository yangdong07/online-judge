// P1008 三连击
// https://www.luogu.org/problemnew/show/P1008

#include <iostream>
#include <cstring>

using namespace std;

bool mark[11] = {false};

bool valid(int n)
{
    while (n)
    {
        if (n % 10 == 0)
            return false;
        if (mark[n % 10])
            return false;
        mark[n % 10] = true;
        n /= 10;
    }
    return true;
}

int main()
{
    for (int n = 123; n <= 333; ++n)
    {
        memset(mark, false, sizeof(mark));
        if (valid(n) && valid(n * 2) && valid(n * 3))
            cout << n << " " << n * 2 << " " << n * 3 << endl;
    }
}