// P1422 小玉家的电费
// https://www.luogu.org/problemnew/show/P1422

#include <cstdio>

int main()
{
    int n;
    double price = 0.0;
    scanf("%d", &n);
    if (n <= 150) {
        price = 0.4463 * n;
    } else if (n <= 400) {
        price = 0.4463 * 150 + (n - 150) * 0.4663;
    } else {
        price = 0.4463 * 150 + (400 - 150) * 0.4663 + (n - 400) * 0.5663;
    }
    printf("%.1f", price);
}