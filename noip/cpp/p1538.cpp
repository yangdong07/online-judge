// P1538 迎春舞会之数字舞蹈
// https://www.luogu.org/problemnew/show/P1538

#include <cstdio>
#include <cstring> 

#define MAX_N 256

const char s[5][10][4] = {
    {" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "},
    {"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |"},
    {"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - "},
    {"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |"},
    {" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "}};

void print_digit(int d, int l, int k)
{
    // d: digit, l: line, k: size

    putchar(s[l][d][0]);
    for (int i = 0; i < k; ++i)
        putchar(s[l][d][1]);
    putchar(s[l][d][2]);
}

void print_digits(int digits[], int n, int k)
{
    int i, j, l;

    for (int l = 0; l < 5; ++l)
    {
        if (l & 1)
        {
            for (j = 0; j < k; ++j)
            {
                for (i = 0; i < n; ++i)
                {
                    print_digit(digits[i], l, k);
                    if (i < n) putchar(' ');
                }
                printf("\n");
            }
        }
        else
        {
            for (i = 0; i < n; ++i)
            {
                print_digit(digits[i], l, k);
                if (i < n) putchar(' ');
            }
            printf("\n");
        }
    }
}


int main(){
    int k;
    char s[MAX_N];
    int digits[MAX_N];
    scanf("%d\n%s", &k, s);
    for (int i = 0; i < strlen(s); ++i)
        digits[i] = s[i] - '0';

    print_digits(digits, strlen(s), 5);
    return 0;
}