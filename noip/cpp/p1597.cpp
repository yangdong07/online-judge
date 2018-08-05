// P1597 语句解析
// https://www.luogu.org/problemnew/show/P1597

#include <cstdio>
#include <cctype>
#include <cstring>

int main()
{
    int value[3] = { 0 };
    char s[100];

    scanf("%s", s);

    for (int i = 0; i < strlen(s); i += 5)
        value[s[i] - 'a'] =
            isdigit(s[i + 3]) ? s[i + 3] - '0' : value[s[i + 3] - 'a'];

    printf("%d %d %d", value[0], value[1], value[2]);
}