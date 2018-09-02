/*
ID: yesimim1
TASK: namenum
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("namenum.in", "r");
    FILE *fout = fopen ("namenum.out", "w");

#include <fstream>
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
*/

#include <cstdio>
#include <cstring>

char s[] = "ABCDEFGHIJKLMNOPRSTUVWXY";
char c2i[26] = {0};

bool match(char name[], char id[])
{
    if (strlen(name) != strlen(id))
        return false;
    
    for (size_t i = 0; i < strlen(name); ++i)
    {
        int c = name[i] - 'A';
        if (c2i[c] != id[i])
            return false;
    }
    return true;
}

int main()
{
    FILE *dict = fopen ("dict.txt", "r");
    FILE *fin = fopen ("namenum.in", "r");
    FILE *fout = fopen ("namenum.out", "w");

    for (int i = 0; i < strlen(s); ++i)
        c2i[s[i] - 'A'] = '0' + i / 3 + 2;

    // for (i = 0; i < 26; ++i)
    //     putchar(i + 'A');
    // fprintf(fout, "\n");
    // for (i = 0; i < 26; ++i)
    //     putchar(c2i[i]);
    // fprintf(fout, "\n");

    char id[100], name[100];
    fscanf(fin, "%s", id);

    bool no_match = true;
    // while (ffscanf(fin, fin, "%s", name) != EOF)
    while (fscanf(dict, "%s", name) != EOF)
    {
        if (match(name, id))
        {
            no_match = false;
            fprintf(fout, "%s\n", name);
        }
    }
    if (no_match)
        fprintf(fout, "NONE\n");
    return 0;
}