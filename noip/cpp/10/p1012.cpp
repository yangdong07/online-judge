// P1012 拼数
// https://www.luogu.org/problemnew/show/P1012

#include <iostream>
#include <algorithm>

using namespace std;

string a[21];

bool cmp(string a, string b)
{
    return a + b > b + a;
}

int main()
{
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n, cmp);
    for (i = 0; i < n; i++)
        cout << a[i];
}