// P1888 三角函数
// https://www.luogu.org/problemnew/show/P1888

#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b)
{
  if (a == 0) return b;
  return gcd(b % a, a);
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    int max_side = max(max(a, b), c);
    int min_side = min(min(a, b), c);
    int side_gcd = gcd(min_side, max_side);

    cout << min_side / side_gcd << "/" << max_side / side_gcd;


}