// P1042 乒乓球
// https://www.luogu.org/problemnew/show/P1042

#include <cstdio>

using namespace std;

#define MAX_N 10000

int main()

{
    char c;
    int i11 = 0, j11 = 0; // 11分制， 计数
    int i21 = 0, j21 = 0; // 21分制， 计数

    int score11[MAX_N][2];
    int score21[MAX_N][2];
    int k11 = 0; // 11分制比分记录索引
    int k21 = 0; // 21分制比分记录索引

    while ((c = getchar()) != 'E')
    {
        if (c == 'W')
            ++i11, ++i21;
        if (c == 'L')
            ++j11, ++j21;
        
        if ((i11 >= 11 && i11 - j11 >= 2) || (j11 >= 11 && j11 - i11 >= 2))
        {
            score11[k11][0] = i11;
            score11[k11++][1] = j11;
            i11 = j11 = 0;
        }
        if ((i21 >= 21 && i21 - j21 >= 2) || (j21 >= 21 && j21 - i21 >= 2))
        {
            score21[k21][0] = i21;
            score21[k21++][1] = j21;
            i21 = j21 = 0;
        }
    }
    for (int i = 0; i < k11; ++i)
        printf("%d:%d\n", score11[i][0], score11[i][1]);
    printf("%d:%d\n\n", i11, j11);

    for (int i = 0; i < k21; ++i)
        printf("%d:%d\n", score21[i][0], score21[i][1]);
    printf("%d:%d", i21, j21);
}