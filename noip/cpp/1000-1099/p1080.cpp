// P1080 国王游戏
// https://www.luogu.org/problemnew/show/P1080

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;


typedef unsigned long long UINT64;
typedef int INT32;

/* 高精度非负整数 */
class BigNumber
{
  private:
    vector<INT32> number;
    static const INT32 BASE = 1000000000; // magic here
    static const INT32 WIDTH = 9;

  public:
    //Constructor
    BigNumber() { }
    BigNumber(UINT64 value)
    {
        number.clear();
        do{
            number.push_back((INT32)(value % BASE));
            value /= BASE;
        } while (value > 0);
    }

    //Allocation
    BigNumber operator=(const BigNumber &a)
    {
        number.clear();
        vector<INT32>::const_iterator it;
        for (it = a.number.begin(); it != a.number.end(); ++it)
            number.push_back(*it);

        return *this;
    }

    //Input&Output
    friend ostream &operator<<(ostream &out, BigNumber const &a)
    {
        if (!a.number.size())
            return out << 0;

        int i = a.number.size() - 1;
        for (; i >= 0 && a.number[i] == 0; --i) ;

        if (i == -1)
            return out << 0;

        vector<int>::const_reverse_iterator it;
        it = a.number.rbegin() + (a.number.size() - i - 1);

        out << *it++;
        for (; it != a.number.rend(); ++it)
            out << setfill('0') << setw(9) << *it;

        return out;
    }

    //Multiplication
    BigNumber &operator*=(unsigned const &n)
    {
        vector<int>::iterator it = number.begin();
        unsigned long long sum = 0;
        for (it = number.begin(); it != number.end(); ++it)
        {
            sum += (unsigned long long)(*it) * n;
            *it = (int)(sum % BASE);
            sum /= BASE;
        }
        if (sum)
            number.push_back((int)sum);

        return *this;
    }

    // Dividing
    BigNumber operator / (INT32 b)
    {
        BigNumber a = *this;
        vector<INT32>::reverse_iterator rit;
        unsigned long long rest = 0;
        for (rit = a.number.rbegin(); rit != a.number.rend(); ++rit)
        {
            rest = rest * BASE + *rit;
            *rit = rest / b;
            rest = rest % b;
        }
        return a;
    }

    //Adding
    BigNumber& operator+=(unsigned long long b)
    {
        vector<int>::iterator it = number.begin();

        unsigned long long sum = 0;
        for (it = number.begin(); it != number.end(); ++it)
        {
            sum = b + *it;
            *it = sum % BASE;
            b = sum / BASE;
        }
        while (sum)
        {
            number.push_back((int)(sum % BASE));
            sum /= BASE;
        }

        return *this;
    }

    BigNumber& operator+=(BigNumber const &b)
    {
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
            *it1 = sum % BASE;
            ++it1;
            sum /= BASE;
        }
        if (sum)
            number.push_back(1);

        return *this;
    }

    //Compare
    int compare(const BigNumber &a) const
    {
        //0 this == a || -1 this < a || 1 this > a
        if (number.size() < a.number.size())
            return -1;
        if (number.size() > a.number.size())
            return 1;

        for (size_t i(number.size()); i > 0; --i)
        {
            if (number[i - 1] < a.number[i - 1])
                return -1;
            if (number[i - 1] > a.number[i - 1])
                return 1;
        }
        return 0;
    }

    bool operator<(BigNumber const &b) const { return compare(b) == -1; }
};

struct LR
{
    int a;
    int b;
};

bool cmp(const LR &a, const LR &b)
{
    return a.a * a.b < b.a * b.b;
}

int main()
{
    const int MAX_N = 1001;
    int n, i;
    LR c[MAX_N];
    cin >> n;
    for (i = 0; i <= n; ++i)
        cin >> c[i].a >> c[i].b;

    sort(c + 1, c + n + 1, cmp);

    BigNumber p = 1, m, max_m = 0;
    for (i = 1; i <= n; ++i)
    {
        p *= c[i - 1].a;
        m = p / c[i].b;
        // printf("%d %d ", c[i].a, c[i].b);
        // cout << p << " " << m << endl;
        if (max_m < m)
            max_m = m;
    }
    cout << max_m << endl;

    return 0;
}