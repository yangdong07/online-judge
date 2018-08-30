// P4326 [COCI2006-2007#1] Herman
// https://www.luogu.org/problemnew/show/P4326

#include <cstdio>

#define PI 3.14159265358979323

int main()
{
    double R;
    scanf("%lf", &R);
    R *= R;
    printf("%lf\n%lf", PI * R, 2.0 * R);
}