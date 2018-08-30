// P1202 [USACO1.1]黑色星期五Friday the Thirteenth
// https://www.luogu.org/problemnew/show/P1202

#include <cstdio>

#define WEEKDAYS 7

bool isLeapYear(int year)
{
    return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    int N, days = 0;
    int weekdays[WEEKDAYS] = {0, 0, 0, 0, 0, 0, 0};
    scanf("%d", &N);
    for (int year = 1900; year < 1900 + N; year++)
    {
        for (int month = 1; month <= 12; month++)
        {
            weekdays[(days + 13) % WEEKDAYS] += 1;
            days += daysInMonth[month];
            if (isLeapYear(year) && month == 2) days++;
        }
    }
    printf("%d", weekdays[6]);
    for (int i = 1; i < WEEKDAYS; ++i)
        printf(" %d", weekdays[(i + 6) % WEEKDAYS]);
}