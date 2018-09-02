
// P1465 序言页码 Preface Numbering
// https://www.luogu.org/problemnew/show/P1465

#include <iostream>
#include <string>

using namespace std;

string roman_dict[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM"}};

string roman_c = "IVXLCDM";

string roman_number(int n)
{
    string s = "";
    for (int t = n, i = 0; t; t /= 10, ++i)
        s = roman_dict[i][t % 10] + s;
    return s;
}

int main()
{
    int n;
    cin >> n;

    string rn;
    int count[26] = {0};

    for (int i = 1; i <= n; i++)
    {
        rn = roman_number(i);
        for (size_t j = 0; j < rn.size(); ++j)
            count[rn[j] - 'A']++;
    }

    string::iterator it;
    for (it = roman_c.begin(); it != roman_c.end(); ++it)
    {
        if (count[*it - 'A'])
            cout << *it << " " << count[*it - 'A'] << endl;;
    }
    return 0;
}