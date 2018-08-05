// P1590 失踪的7
// https://www.luogu.org/problemnew/show/P1590

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_N 100

int main()
{
    int t, i;
    char a[MAX_N];
    int len, pascals;

    cin >> t;
    while (t--)
    {
        cin >> a;
        len = strlen(a);
        for (i = 0; i < len; i++)
            if (a[i] == '7')
            {
                a[i] = '6';
                break;
            }
        for (++i; i < len; i++)
            a[i] = '9';

        for (i = 0, pascals = 0; i < len; ++i)
            pascals = pascals * 9 + a[i] - '0' - (a[i] > '7');
        cout << pascals << endl;
    }
    return 0;
}