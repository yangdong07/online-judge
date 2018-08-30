// P1085 不高兴的津津
// https://www.luogu.org/problemnew/show/P1085

#include <cstdio>
#include <algorithm>

using namespace std;

#define WEEK_DAYS 7

int main() {
    int meitounao, bugaoxing;
    int day = 0, unhappy, max_unhappy = 0;
    for (int i = 1; i <= WEEK_DAYS; ++i) {
        scanf("%d %d", &meitounao, &bugaoxing);
        unhappy = max(0, meitounao + bugaoxing - 8);
        if (unhappy > max_unhappy) {
            day = i;
            max_unhappy = unhappy;
        }
    }
    printf("%d", day);
}