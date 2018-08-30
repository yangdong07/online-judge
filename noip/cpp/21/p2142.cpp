// P2142 高精度减法
// https://www.luogu.org/problemnew/show/P2142

#include <iostream>
#include <string>

using namespace std;

string subtract(string num1, string num2)
{
    int l1 = num1.length(), l2 = num2.length();
    string sub = l1 > l2 ? num1 : num2;

    if (l1 > l2)
        num2.insert(0, l1 - l2, '0');
    else
        num1.insert(0, l2 - l1, '0'); // padding zeros
    
    bool negative = num1 < num2;
    if (negative) num1.swap(num2);

    for (int i = num1.length() - 1; i >= 0; --i)
    {
        if (num1[i] < num2[i])
        {
            num1[i] += 10;
            num1[i - 1]--;
        }
        sub[i] = ((num1[i] - '0') - (num2[i] - '0')) + '0';
    }
    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);
    
    if (negative) sub.insert(0, 1, '-');

    return sub;
}
int main()
{
    string a, b;
    cin >> a >> b;
    cout << subtract(a, b) << endl;
    return 0;
}