// P1046 陶陶摘苹果
// https://www.luogu.org/problemnew/show/P1046

#include <iostream>
#include <cstdio>

using namespace std;

int main() {

    int a[10];
    int height, count = 0;
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &height);
    height += 30;
    for (int i = 0; i < 10; i++) {
        if (height >= a[i]) {
            count++;
        }
    }
    printf("%d", count);
}