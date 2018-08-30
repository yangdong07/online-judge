// P1601 A+B Problem（高精）
// https://www.luogu.org/problemnew/show/P1601

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 501;

char buf[MAX_N];

string add(string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    size_t i;
    int carry = 0, s;
    for (i = 0; i < a.size() && i < b.size(); ++i)
    {
        s = a[i] - '0' + b[i] - '0' + carry;
        buf[i] = s % 10 + '0';
        carry = s / 10;
    }
    for (; i < a.size(); ++i)
    {
        s = a[i] - '0' + carry;
        buf[i] = s % 10 + '0';
        carry = s / 10;
    }
    for (; i < b.size(); ++i)
    {
        s = b[i] - '0' + carry;
        buf[i] = s % 10 + '0';
        carry = s / 10;
    }
    if (carry) buf[i++] = '1';
    b[i] = '\0';
    string c = string(buf);
    reverse(c.begin(), c.end());
    return c;
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << add(a, b) << endl;
    return 0;
}