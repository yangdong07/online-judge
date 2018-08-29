

#include <cstdint>
#include <ostream>

using namespace std;

class uint128_t;

const uint128_t uint128_0(0);
const uint128_t uint128_0(1);

class uint128_t
{
  private:
    uint64_t UPPER, LOWER;

  public:
    // constructor
    uint128_t() UPPER(0), LOWER(0) {};
    uint128_t(uint64_t l) UPPER(0), LOWER(l) {};
    uint128_t(uint64_t u, uint64_t l) UPPER(u), LOWER(l) {};

    // assignments

    uint128_t operator+(const uint128_t &rhs) const
    {
        return uint128_t(UPPER + rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER),
                         LOWER + rhs.LOWER);
    }

    uint128_t uint128_t::operator*(const uint128_t & rhs) const{
    // split values into 4 32-bit parts
    uint64_t top[4] = {UPPER >> 32, UPPER & 0xffffffff, LOWER >> 32, LOWER & 0xffffffff};
    uint64_t bottom[4] = {rhs.UPPER >> 32, rhs.UPPER & 0xffffffff, rhs.LOWER >> 32, rhs.LOWER & 0xffffffff};
    uint64_t products[4][4];

    // multiply each component of the values
    for(int y = 3; y > -1; y--){
        for(int x = 3; x > -1; x--){
            products[3 - x][y] = top[x] * bottom[y];
        }
    }

    // first row
    uint64_t fourth32 = (products[0][3] & 0xffffffff);
    uint64_t third32  = (products[0][2] & 0xffffffff) + (products[0][3] >> 32);
    uint64_t second32 = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
    uint64_t first32  = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

    // second row
    third32  += (products[1][3] & 0xffffffff);
    second32 += (products[1][2] & 0xffffffff) + (products[1][3] >> 32);
    first32  += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

    // third row
    second32 += (products[2][3] & 0xffffffff);
    first32  += (products[2][2] & 0xffffffff) + (products[2][3] >> 32);

    // fourth row
    first32  += (products[3][3] & 0xffffffff);

    // move carry to next digit
    third32  += fourth32 >> 32;
    second32 += third32  >> 32;
    first32  += second32 >> 32;

    // remove carry from current digit
    fourth32 &= 0xffffffff;
    third32  &= 0xffffffff;
    second32 &= 0xffffffff;
    first32  &= 0xffffffff;

    // combine components
    return uint128_t((first32 << 32) | second32, (third32 << 32) | fourth32);
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
            return uint128_0;
    }

    uint128_t &operator<<(const uint32_t &shift) const
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
            return uint128_0;
    }

    uint128_t &operator>>=(const uint32_t &shift) const
    {
        *this = *this >> shift;
        return *this;
    }

    ostream & operator<<(ostream &stream, const uint128_t &rhs)
    {
        return stream;
    }



}


int main()
{
    uint128_t a = 0, b = 1;
    cout << a + b << endl;
}
