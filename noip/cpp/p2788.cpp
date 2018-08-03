// P2788 数学1（math1）- 加减算式
// https://www.luogu.org/problemnew/show/P2788

#include <cstdio>
#include <cctype>

int main()
{
    char c;
    int number = 0, answer = 0;
    char op = '+';
    while ((c = getchar()) != EOF)
    {
        if (c == '+' || c == '-')  //calc
        {
            answer += (op == '+' ? number : -number);
            op = c;
            number = 0;
        }
        else if (isdigit(c))
        {
            number = number * 10 + (c - '0');
        }
    }
    answer += (op == '+' ? number : -number);
    printf("%d", answer);
}