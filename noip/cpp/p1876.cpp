// P1876 开灯
// https://www.luogu.org/problemnew/show/P1876

#include <iostream>

using namespace std;

int main()
{
    long long n, i = 1, a;
    cin >> n;

    while (1)
    {
        a = i * i;
        if (a > n)
            break;

        cout << a << " ";
        i++;
    } 
}