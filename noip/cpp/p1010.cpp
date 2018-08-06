// P1010 幂次方
// https://www.luogu.org/problemnew/show/P1010

#include <iostream>
#include <string>

using namespace std;


string expression(int n)
{
    string s = "";
    if (n & 1) s = string("+2(0)") + s;
    if (n & 2) s = string("+2") + s;

    for (int i = 4, c = 2; i <= n; i <<= 1, ++c)
    {
        if (n & i) s = string("+2(") + expression(c) + string(")") + s;
    }
    return s.substr(1);
}

int main()
{
    int n;
    cin >> n;
    cout << expression(n) << endl;

}