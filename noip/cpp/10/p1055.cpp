// P1055 ISBN号码
// https://www.luogu.org/problemnew/show/P1055


#include <iostream>

const int MAX_SIZE = 15;

int main() {
    char s[MAX_SIZE], code[12] = "0123456789X";
    char *p = s;
    int i, j = 0, t = 0;
    scanf("%s", s);
    // 0-670-82162-4
    for (i = 0; i < 12; i++) {
        if (s[i] != '-') {
            t += (s[i] - '0') * (++j);
        }
    }
    if (s[i] == code[t % 11]) {
        printf("Right");
    } else {
        s[i] = code[t % 11];
        printf("%s", s);
    }
}