// P1200 [USACO1.1]你的飞碟在这儿Your Ride Is He…
// https://www.luogu.org/problemnew/show/P1200


#include <cstdio>

#define BUF_SIZE 10

int main()
{
    int code1 = 1, code2 = 1;
    char buf[BUF_SIZE];
    scanf("%s", buf);
    char *p = buf;
    while (*p) 
        code1 *= (*p++ - 'A' + 1);
    scanf("%s", buf);
    p = buf;
    while (*p) 
        code2 *= (*p++ - 'A' + 1);
    if (code1 % 47 == code2 % 47) printf("GO");
    else printf("STAY");
}