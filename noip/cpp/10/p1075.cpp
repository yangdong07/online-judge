// P1075 质因数分解
// https://www.luogu.org/problemnew/show/P1075

#include <iostream>

using namespace std;


int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            printf("%d", n / i);
            return 0;
        }
    }
}