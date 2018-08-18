// P1226 【模板】快速幂||取余运算
// https://www.luogu.org/problemnew/show/P1226

#include <cstdio>

using namespace std;

typedef long long INT64;

int main()
{
    INT64 b, p, k;
    scanf("%lld %lld %lld", &b, &p, &k);

    INT64 a = b, t = p;
    INT64 result = t == 0 ? (1 % k) : 1;

    while (t)
    {
        if (t & 1)
            result = (result * a) % k;
        
        a = (a * a) % k;
        t >>= 1;
    }

    printf("%lld^%lld mod %lld=%lld\n", b, p, k, result);

    return 0;
}