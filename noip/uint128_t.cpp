
#include <iostream>
#include <cstdint>
#include <ostream>

using namespace std;

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

    bool operator==(const uint128_t &rhs) const
    {
        return ((UPPER == rhs.UPPER) && (LOWER == rhs.LOWER));
    }

    pair<uint128_t, uint32_t> divmod(const uint32_t &divisor) const
    {
        if (divisor == 0)
            throw domain_error("Error: division or modulus by 0");
        else if (divisor == 1)
            return pair<uint128_t, uint32_t>(*this, 0);
        
        uint64_t parts[4] = {UPPER >> 32, UPPER & 0xffffffff, LOWER >> 32, LOWER & 0xffffffff};
        uint64_t d, r = 0, q[4];
        for (int i = 0; i < 4; ++i)
        {
            d = (r << 32) + parts[i];
            q[i] = d / divisor;
            r = d % divisor;
        }
        return pair<uint128_t, uint32_t>(uint128_t((q[0] << 32) | q[1], (q[2] << 32) | q[3]), (uint32_t)r);
    }

    bool operator!() const { return !(bool)(UPPER | LOWER); }
    operator bool() const { return (bool)(UPPER | LOWER); }

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

    uint128_t operator<<(const uint32_t &shift) const
    {
        if (shift == 0)
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

    uint128_t & operator<<=(const uint32_t &shift)
    {
        *this = *this << shift; 
        return *this; 
    }

    uint128_t operator>>(const uint32_t &shift) const
    {
        if (shift == 0)
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

    uint128_t & operator>>=(const uint32_t &shift)
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

typedef pair<uint128_t, uint32_t> QR;

int main()
{
    uint128_t a = 100, b = 33;

    QR qr = a.divmod(33);

    cout << qr.first << endl;

    cout << a + b << endl;
}
