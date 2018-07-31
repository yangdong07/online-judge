// P1089 津津的储蓄计划
// https://www.luogu.org/problemnew/show/P1089

#include <cstdio>

using namespace std;

#define MONTHS 12

int main() {
    int budget, saved=0, rest=0;
    int X = 0;
    for (int i = 1; i <= MONTHS; i++) {
        scanf("%d", &budget);
        rest = rest + 300 - budget;
        if (X == 0 && rest < 0) {
            X = i;
        } else if (rest > 0) {
            saved += (rest / 100);
            rest %= 100;
        }
    }
    if (X == 0) {
        printf("%d", rest + saved * 120);
    } else {
        printf("-%d", X);
    }
}