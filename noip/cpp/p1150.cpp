// P1150 `Peter`的烟
// https://www.luogu.org/problemnew/show/P1150

#include <cstdio>
#include <algorithm>

using namespace std;

int main() 
{
    int n, k;
    scanf("%d %d", &n, &k);

    int m = n, smoke = n, next_smoke;  // init
    while (m >= k) {
        next_smoke = m / k;
        smoke += next_smoke;
        m = next_smoke + m % k;
    }
    // if (m == k - 1) // credit?
    //     smoke += 1;
    printf("%d", smoke);
}