// P1028 数的计算
// https://www.luogu.org/problemnew/show/P1028

#include <iostream>

using namespace std;

#define MAX_N 1001

int a[MAX_N] = { 0 };

int f(int n)
{
    if (a[n])
        return a[n];
    
    if (n & 1)
        a[n] = f(n - 1);
    else
        a[n] = f(n - 1) + f(n / 2);

    return a[n];
}


int main()
{
    int n;
    cin >> n;

    a[0] = a[1] = 1;
    a[2] = a[3] = 2;

    cout << f(n);
}