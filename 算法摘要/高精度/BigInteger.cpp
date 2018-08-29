/*
    https://github.com/panks/BigInteger/blob/master/BigIntegerSingleFile.cpp
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef unsigned long long UINT64;
typedef int INT32;

#define MAX_N 65535

char buf[MAX_N];

/* 高精度整数 */
class BigInteger
{
  public:
    string number;
    bool negative;
    
    string add(string num1, string num2)
    {
        int l1 = num1.length(), l2 = num2.length();
        string sum = l1 > l2 ? num1 : num2;

        if (l1 > l2)
            num2.insert(0, l1 - l2, '0');
        else
            num1.insert(0, l2 - l1, '0');  // padding zeros

        char carry = '0';
        for (int i = sum.size() - 1; i >= 0; --i)
        {
            add[i] = (carry - '0') + (num1[i] - '0') + (num2[i] - '0') + '0';
            if (add[i] > '9') { add[i] -= 10; carry = '1'; }
            else { carry = '0'; }
        }
        if (carry == '1')
            add.insert(0, 1, '1');
        return add;
    }

    string subtract(string num1, string num2)
    {
        int l1 = num1.length(), l2 = num2.length();
        string sub = l1 > l2 ? num1 : num2;

        if (l1 > l2)
            num2.insert(0, l1 - l2, '0');
        else
            num1.insert(0, l2 - l1, '0');  // padding zeros

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

        return sub;
    }
}