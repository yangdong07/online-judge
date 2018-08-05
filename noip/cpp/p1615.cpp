// P1615 西游记公司
// https://www.luogu.org/problemnew/show/P1615

#include <cstdio>

int main()
{
    long long h1, m1, s1;
    long long h2, m2, s2;
    long long speed;
    scanf("%lld:%lld:%lld", &h1, &m1, &s1);
    scanf("%lld:%lld:%lld", &h2, &m2, &s2);
    scanf("%lld", &speed);

    printf("%lld", ((h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1)) * speed);
}