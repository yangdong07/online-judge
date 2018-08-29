// P1255 数楼梯
// https://www.luogu.org/problemnew/show/P1255

#include <iostream>

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

int main()
{
    int n, i;
    cin >> n;

    if (n < 3)
    {
        cout << n << endl;
        return 0;
    }

    string f1 = "1", f2 = "2", f3;
    for (i = 3; i <= n; ++i)
    {
        f3 = add(f1, f2);
        f1 = f2; f2 = f3;
    }

    cout << f3 << endl;
    return 0;
}