// P4710 「物理」平抛运动
// https://www.luogu.org/problemnew/show/P4710

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double g = 10.0;
    double v, theta;
    cin >> v >> theta;

    double t = v * cos(theta) / g;
    double x0 = v * sin(theta) * t;
    double y0 = 0.5 * g * t * t;

    cout << x0 << " " << y0;

}