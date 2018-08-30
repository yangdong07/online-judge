// P1618 三连击（升级版）
// https://www.luogu.org/problemnew/show/P1618


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
    int a, b, c;
    cin >> a >> b >> c;

    bool no_valid = true;

    int n = 123;
    while (n % a != 0) ++n;

    for ( ; n <= 999; n += a)
    {
        memset(mark, false, sizeof(mark));
        if (valid(n) && valid(n / a * b) && valid(n / a * c))
        {
            no_valid = false;
            cout << n << " " << n / a * b << " " << n / a * c << endl;
        }
    }
    if (no_valid)
        cout << "No!!!";
}