// P1011 车站
// https://www.luogu.org/problemnew/show/P1011

#include <iostream>

using namespace std;

#define MAX_N 22

int main()
{
    int f[MAX_N];
    f[0] = 0;
    f[1] = 1;
    
    for (int i = 2; i < MAX_N; ++i)
        f[i] = f[i - 1] + f[i - 2];

    int a, n, m, x;
    cin >> a >> n >> m >> x;

    int as[MAX_N], bs[MAX_N];
    as[1] = as[2] = 1; // a@1, a@2
    bs[1] = bs[2] = 0; // b@1, b@2
    as[3] = 2;  bs[3] = 0;
    for (int i = 4; i < n; ++i)
    {
        as[i] = as[i - 1] + f[i - 4];
        bs[i] = bs[i - 1] + f[i - 3];
    }

    int b = (m - a * as[n - 1]) / bs[n-1];

    // cout << b << endl;
    cout << a * as[x] + b * bs[x] << endl;

}