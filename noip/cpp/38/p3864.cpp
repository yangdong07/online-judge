
// P3864 [USACO1.2]命名那个数字 Name That Number
// https://www.luogu.org/problemnew/show/P3864

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
    // FILE *fin = fopen ("test.txt", "r");

    for (int i = 0; i < strlen(s); ++i)
        c2i[s[i] - 'A'] = '0' + i / 3 + 2;

    // for (i = 0; i < 26; ++i)
    //     putchar(i + 'A');
    // printf("\n");
    // for (i = 0; i < 26; ++i)
    //     putchar(c2i[i]);
    // printf("\n");

    char id[100], name[100];
    scanf("%s", id);

    bool no_match = true;
    // while (fscanf(fin, "%s", name) != EOF)
    while (scanf("%s", name) != EOF)
    {
        if (match(name, id))
        {
            no_match = false;
            printf("%s\n", name);
        }
    }
    if (no_match)
        printf("NONE\n");
    return 0;
}