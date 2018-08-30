// P1005 矩阵取数游戏
// https://www.luogu.org/problemnew/show/P1005

#include <iostream>
#include <ostream>

using namespace std;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;

class uint128_t
{
  private:
    uint64_t UPPER, LOWER;

  public:
    // constructor
    uint128_t(): UPPER(0), LOWER(0) {}
    uint128_t(uint64_t l): UPPER(0), LOWER(l) {}
    uint128_t(uint64_t h, uint64_t l): UPPER(h), LOWER(l) {}

    // assignments
    uint128_t operator+(const uint128_t &rhs) const
    {
        return uint128_t(UPPER + rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER),
                         LOWER + rhs.LOWER);
    }

    uint128_t &operator+=(const uint128_t &rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    bool operator>(const uint128_t &rhs) const
    {
        if (UPPER == rhs.UPPER)
            return (LOWER > rhs.LOWER);
        return (UPPER > rhs.UPPER);
    }

    // bool operator==(const uint128_t &rhs) const
    // {
    //     return ((UPPER == rhs.UPPER) && (LOWER == rhs.LOWER));
    // }

    pair<uint128_t, uint32_t> divmod(const uint32_t &divisor) const
    {
        if (divisor == 0)
            throw domain_error("Error: division or modulus by 0");
        else if (divisor == 1)
            return pair<uint128_t, uint32_t>(*this, 0);
        
        uint64_t q[4] = {UPPER >> 32, UPPER & 0xffffffff, LOWER >> 32, LOWER & 0xffffffff};
        uint64_t d, r = 0;
        for (int i = 0; i < 4; ++i)
        {
            d = (r << 32) + q[i];
            q[i] = d / divisor;
            r = d % divisor;
        }
        return pair<uint128_t, uint32_t>(uint128_t((q[0] << 32) | q[1], (q[2] << 32) | q[3]), (uint32_t)r);
    }

    operator bool() const { return (bool)(UPPER | LOWER); }
    bool operator!() const { return !(bool)(UPPER | LOWER); }

    string str(const uint32_t base = 10) const
    {
        if ((base < 2) || (base > 16))
            throw invalid_argument("Base must be in the range [2, 16]");
        
        if (!(*this)) return "0";
        string out = "";
        pair<uint128_t, uint32_t> qr(*this, 0);
        do
        {
            qr = qr.first.divmod(base);
            out = "0123456789abcdef"[qr.second] + out;
        } while (qr.first);
        return out;
    }

    uint128_t operator<<(const int &shift) const
    {
        if (shift < 0)
            return *this >> -shift;
        else if (shift == 0)
            return *this;
        else if (shift < 64)
            return uint128_t((UPPER << shift) + (LOWER >> (64 - shift)),
                             LOWER << shift);
        else if (shift == 64)
            return uint128_t(LOWER, 0);
        else if (shift < 128)
            return uint128_t(LOWER << (shift - 64), 0);
        else
            return uint128_t(0);
    }

    uint128_t & operator<<=(const int &shift)
    {
        *this = *this << shift; 
        return *this; 
    }

    uint128_t operator>>(const int &shift) const
    {
        if (shift < 0)
            return *this << -shift;
        else if (shift == 0)
            return *this;
        else if (shift < 64)
            return uint128_t(UPPER >> shift,
                             (UPPER << (64 - shift)) + (LOWER >> shift));
        else if (shift == 64)
            return uint128_t(0, UPPER);
        else if (shift < 128)
            return uint128_t(0, (UPPER >> (shift - 64)));
        else
            return uint128_t(0);
    }

    uint128_t & operator>>=(const int &shift)
    {
        *this = *this >> shift;
        return *this;
    }

};

ostream &operator<<(ostream &stream, const uint128_t &rhs)
{
    stream << rhs.str();
    return stream;
}

uint128_t max_num(const uint128_t &a, const uint128_t &b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 81;
    uint128_t a[MAX_N], dp[MAX_N], result = 0;

    int n, m, i, j, k, tmp;
    cin >> n >> m;

    for (i = 0; i < n; ++i)
    {
        // input
        for (j = 0; j < m; ++j)
        {
            cin >> tmp;
            a[j] = uint128_t(tmp);
            dp[j] = a[j] << m;
        }

        // dp
        for (k = 1; k < m; ++k)
            for (int l = 0; l < m - k; ++l)
                dp[l] = max_num(dp[l] + (a[l + k] << (m - k)),
                                dp[l + 1] + (a[l] << (m - k)));
        result += dp[0];
    }

    cout << result.str() << endl;

    return 0; 
}


/* solution1, using binary */

// #include <iostream>
// #include <string>

// using namespace std;

// char i2c[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// int c2i(char c)
// {
//     if (c >= '0' && c <= '9')
//         return c - '0';
//     else
//         return c - 'A' + 10;
// }

// string lshift(string num, size_t n)
// {
//     num.append(n, '0');
//     return num;
// }

// int compare(const string &num1, const string &num2)
// {
//     int l1 = num1.size(), l2 = num2.size();
//     if (l1 > l2)
//         return 1;
//     else if (l1 < l2)
//         return -1;
//     else
//         return num1.compare(num2);
// }

// string max_num(string num1, string num2)
// {
//     return compare(num1, num2) > 0 ? num1 : num2;
// }

// void self_add(string &num1, string num2, int base = 10)
// {
//     int l1 = num1.length(), l2 = num2.length();

//     if (l1 > l2)
//         num2.insert(0, l1 - l2, '0');
//     else
//         num1.insert(0, l2 - l1, '0');
//     int carry = 0, i, t;
//     for (i = num1.size() - 1; i >= 0; --i)
//     {
//         t = (num1[i] - '0') + (num2[i] - '0') + carry;
//         num1[i] = '0' + (t % base);
//         carry = t / base;
//     }
//     if (carry) num1.insert(0, 1, '1');
// }

// string multiply(string a, int b, int base)
// {
//     if (!b) return "0";

//     string result = "";
//     int digit, carry = 0;
//     for (int i = a.length() - 1; i >= 0; --i)
//     {
//         digit = c2i(a[i]) * b + carry;
//         result.insert(0, 1, i2c[digit % base]);
//         carry = digit / base;
//     }
//     for (; carry; carry /= base)
//         result.insert(0, 1, i2c[carry % base]);
//     return result;
// }

// string add(string num1, string num2, int base)
// {
//     string sum = num1;
//     self_add(sum, num2, base);
//     return sum;
// }

// string i2s(int n, int base)
// {
//     string s = "";
//     for (int t = n; t; t /= base)
//         s.insert(0, 1, (char)('0' + t % base));
//     return s;
// }

// string convert2decimal(string s, int base)
// {
//     string decimal = "0";
//     string power = "1";
//     for (int i = s.size() - 1; i >= 0; --i)
//     {
//         self_add(decimal, multiply(power, c2i(s[i]), 10));
//         power = multiply(power, base, 10);
//     }
//     return decimal;
// }

// int main()
// {
//     const int MAX_N = 81;
//     string a[MAX_N], dp[MAX_N];

//     int n, m, i, j, k, tmp;
//     cin >> n >> m;

//     // string a1 = "12345";
//     // string a2 = "123455555";
//     // cout << compare(a1, a2) << endl;
//     // cout << add(a1, a2, 10) << endl;
//     // cout << convert2decimal("11", 2) << endl;
//     // cout << convert2decimal("11000", 2) << endl;
//     string result = "0";

//     for (i = 0; i < n; ++i)
//     {
//         // input
//         for (j = 0; j < m; ++j)
//         {
//             cin >> tmp;
//             a[j] = i2s(tmp, 2);
//             dp[j] = lshift(a[j], m);   // 
//         }

//         // dp
//         for (k = 1; k < m; ++k)
//         {
//             for (int l = 0; l < m - k; ++l)
//                 dp[l] = max_num(add(dp[l], lshift(a[l + k], m - k), 2),
//                             add(dp[l + 1], lshift(a[l], m - k), 2));
//             // for (int l = 0; l < m - k; ++l)
//             //     cout << convert2decimal(dp[l], 2) << " ";
//             // cout << endl;
//         }
//         // cout << convert2decimal(dp[0], 2) << endl;
//         self_add(result, dp[0], 2);
//     }

//     cout << convert2decimal(result, 2) << endl;

//     return 0;
// }