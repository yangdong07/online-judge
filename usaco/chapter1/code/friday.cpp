/*
ID: yesimim1
TASK: friday
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("friday.in", "r");
    FILE *fout = fopen ("friday.out", "w");

#include <fstream>
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
*/

#include <cstdio>

#define WEEKDAYS 7

bool isLeapYear(int year)
{
    return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    FILE *fin = fopen ("friday.in", "r");
    FILE *fout = fopen ("friday.out", "w");

    int N, days = 0;
    int weekdays[WEEKDAYS] = {0, 0, 0, 0, 0, 0, 0};
    fscanf(fin, "%d", &N);
    for (int year = 1900; year < 1900 + N; year++)
    {
        for (int month = 1; month <= 12; month++)
        {
            weekdays[(days + 13) % WEEKDAYS] += 1;
            days += daysInMonth[month];
            if (isLeapYear(year) && month == 2) days++;
        }
    }
    fprintf(fout, "%d", weekdays[6]);
    for (int i = 1; i < WEEKDAYS; ++i)
        fprintf(fout, " %d", weekdays[(i + 6) % WEEKDAYS]);
    fprintf(fout, "\n");
}