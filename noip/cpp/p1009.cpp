// P1009 阶乘之和
// https://www.luogu.org/problemnew/show/P1009

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class BigNumber
{
  private:
    vector<int> number;
    bool positive;
    static const int base = 1000000000; // magic here

  public:
    //Constructor
    BigNumber() { positive = true; }
    BigNumber(long long value)
    {
        positive = value >= 0;
        if (!positive)
            value = -value;

        while (value)
        {
            number.push_back((int)(value % base));
            value /= base;
        }
    }

    //Input&Output
    friend ostream &operator<<(ostream &out, BigNumber const &a)
    {
        if (!a.number.size())
            return out << 0;
        int i = a.number.size() - 1;
        for (; i >= 0 && a.number[i] == 0; --i)
            ;

        if (i == -1)
            return out << 0;

        if (!a.positive)
            out << '-';

        vector<int>::const_reverse_iterator it = a.number.rbegin() + (a.number.size() - i - 1);

        out << *it++;
        for (; it != a.number.rend(); ++it)
            out << setfill('0') << setw(9) << *it;

        return out;
    }

    //Multiplication
    BigNumber &operator*=(int const &n)
    {
        vector<int>::iterator it = number.begin();
        long long sum = 0;
        while (it != number.end())
        {
            sum += (long long)(*it) * n;
            *it = (int)(sum % base);
            sum /= base;
            ++it;
        }
        if (sum)
            number.push_back((int)sum);

        return *this;
    }

    //Adding
    BigNumber& operator+=(BigNumber const &b)
    {
        if (!b.positive)
        {
            return *this -= b;
        }
        vector<int>::iterator it1 = number.begin();
        vector<int>::const_iterator it2 = b.number.begin();
        int sum = 0;
        while (it1 != number.end() || it2 != b.number.end())
        {
            if (it1 != number.end())
            {
                sum += *it1;
            }
            else
            {
                number.push_back(0);
                it1 = number.end() - 1;
            }
            if (it2 != b.number.end())
            {
                sum += *it2;
                ++it2;
            }
            *it1 = sum % base;
            ++it1;
            sum /= base;
        }
        if (sum)
            number.push_back(1);

        return *this;
    }

    BigNumber& operator-=(BigNumber const &b)
    {
        vector<int>::iterator it1 = number.begin();
        vector<int>::const_iterator it2 = b.number.begin();
        int dif = 0;
        while (it1 != number.end() || it2 != b.number.end())
        {
            if (it1 != number.end())
            {
                dif += *it1;
                ++it1;
            }
            if (it2 != b.number.end())
            {
                dif -= *it2;
                ++it2;
            }
            if (dif < 0)
            {
                *(it1 - 1) = dif + base;
                dif = -1;
            }
            else
            {
                *(it1 - 1) = dif % base;
                dif /= base;
            }
        }
        if (dif < 0)
            positive = false;

        if (number.size() > 1)
        {
            do
            {
                it1 = number.end() - 1;
                if (*it1 == 0)
                    number.pop_back();
                else
                    break;
            } while (number.size() > 1);
        }

        return *this;
    }
};

int main()
{
    int n, i;
    cin >> n;

    BigNumber factorial = 1, sum = 0;

    for (i = 1; i <= n; ++i)
    {
        factorial *= i;
        sum += factorial;
    }
    // cout << factorial << endl;
    cout << sum << endl;
}