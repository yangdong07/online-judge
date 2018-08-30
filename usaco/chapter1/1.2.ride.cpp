/*
ID: yeimim1
TASK: ride
LANG: C++                 
*/

#include <fstream>
#include <cstdio>

#define BUF_SIZE 10

int main()
{
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");

    int code1 = 1, code2 = 1;
    char buf[BUF_SIZE];
    fscanf(fin, "%s", buf);
    char *p = buf;
    while (*p) 
        code1 *= (*p++ - 'A' + 1);
    fscanf(fin, "%s", buf);
    p = buf;
    while (*p) 
        code2 *= (*p++ - 'A' + 1);
    if (code1 % 47 == code2 % 47) fprintf(fout, "GO\n");
    else fprintf(fout, "STAY\n");
}