
// P1015 回文数
// https://www.luogu.org/problemnew/show/P1015


#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int c2i(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return 0;
}

bool is_palindrome(string &s)
{
    int l = 0, r = s.size() - 1;

    while (l < r)
        if (s[l++] != s[r--])
            return false;
    return true;
}

string palindrome_add(string a, int base)
{
    string b = a;
    reverse(b.begin(), b.end());

    string s = "";
    int len = (int)a.size(), i;
    int carry = 0, sum;
    for (i = 0; i < len; ++i)
    {
        sum = c2i(a[i]) + c2i(b[i]) + carry;
        s.insert(0, 1, "0123456789ABCDEFGHIJKL"[sum % base]);
        carry = sum / base;
    }
    if (carry)
        s.insert(0, 1, "0123456789ABCDEFGHIJKL"[carry]);

    return s;
}

int main()
{
    int base;
    string s;
    cin >> base >> s;

    bool impossible = true;

    for (int i = 1; i <= 30; ++i)
    {
        s = palindrome_add(s, base);
        if (is_palindrome(s))
        {
            impossible = false;
            cout << "STEP=" << i << endl;
            return 0;
        }
    }
    if (impossible)
        cout << "Impossible!" << endl;

    return 0;
}