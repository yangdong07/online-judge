// P1449 后缀表达式
// https://www.luogu.org/problemnew/show/P1449

#include <cstdio>

int main()
{
    const int MAX_N = 1000;
    char c;
    int num = 0;
    int stack[MAX_N], k = 0;
    while ((c = getchar()) != '@')
    {
        if (c >= '0' && c <= '9')
            num = num * 10 + c - '0';
        else if (c == '.')
        {
            stack[k++] = num;
            num = 0;
        }
        else if (c == '-')
        {
            stack[k - 2] -= stack[k - 1];
            --k;
        }
        else if (c == '+')
        {
            stack[k - 2] += stack[k - 1];
            --k;
        }
        else if (c == '*')
        {
            stack[k - 2] *= stack[k - 1];
            --k;
        }
        else if (c == '/')
        {
            stack[k - 2] /= stack[k - 1];
            --k;
        }
    }

    printf("%d", stack[0]);
    return 0;
}