// P1303 A*B Problem
// https://www.luogu.org/problemnew/show/P1303


#include <iostream>
#include <string>

using namespace std;

string add(string num1, string num2)
{
    int l1 = num1.length(), l2 = num2.length();

    if (l1 > l2)
        num2.insert(0, l1 - l2, '0');
    else
        num1.insert(0, l2 - l1, '0');

    string sum = num1;
    char carry = 0;

    for (int i = sum.size() - 1; i >= 0; --i)
    {
        sum[i] += (carry + num2[i] - '0');
        if (sum[i] > '9')
        {
            sum[i] -= 10;
            carry = 1;
        }
        else
            carry = 0;
    }
    if (carry) sum.insert(0, 1, '1');
    return sum;
}

string multiply(string n1, string n2)
{
    if (n1.length() > n2.length()) n1.swap(n2);
    int l1 = n1.length(), l2 = n2.length();  // l1 < l2

    string res = "0";
    // for every digit in n2, multiply short n1, then add
    for (int i = l1 - 1; i >= 0; --i)
    {
        string t = n2;
        int digit = n1[i] - '0';
        int carry = 0;

        for (int j = l2 - 1; j >= 0; --j)
        {
            t[j] = ((t[j] - '0') * digit) + carry;  // max 9 * 9 = 81
            if (t[j] > 9)
            {
                carry = (t[j] / 10);
                t[j] -= (carry * 10);
            }
            else
                carry = 0;
            t[j] += '0'; // back to string mood
        }

        if (carry > 0)
            t.insert(0, 1, (char)(carry + '0'));

        t.append(l1 - i - 1, '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add(res, t);   // O(n)
    }

    while (res[0] == '0' && res.length() != 1) // erase leading zeros
        res.erase(0, 1);

    return res;
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << multiply(a, b) << endl;
    return 0;
}