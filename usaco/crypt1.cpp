/*
ID: yesimim1
TASK: crypt1
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("crypt1.in", "r");
    FILE *fout = fopen ("crypt1.out", "w");

#include <fstream>
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");
*/

#include <cstdio>


bool valid[10] = {false}; // 标记有效数字


bool is_valid(int n)
{
    for (; n; n /= 10)
        if (!valid[n % 10]) return false;
    return true;
}


bool check(int a, int b)
{
    if (!is_valid(a) || !is_valid(b))
        return false;

    int ab1 = a * (b % 10);
    int ab2 = a * (b / 10);
    int result = a * b;

    if (ab1 > 999 || b > 999 || result > 9999)
        return false;

    return is_valid(ab1) && is_valid(ab2) && is_valid(result);
}

int main()
{
    FILE *fin = fopen("crypt1.in", "r");
    FILE *fout = fopen("crypt1.out", "w");
    int n, i, j;
    fscanf(fin, "%d", &n);
    int digit;
    for (i = 0; i < n; i++)
    {
        fscanf(fin, "%d", &digit);
        valid[digit] = true;
    }
    int solution = 0;
    for (i = 100; i < 1000; i++)
        for (j = 10; j < 100; j++)
            if (check(i, j)) solution++;

    fprintf(fout, "%d\n", solution); //输出
    return 0;
}