// P1308 统计单词数
// https://www.luogu.org/problemnew/show/P1308

#include <cstdio>
#include <cstring>
#include <cctype>

bool compare(char *a, char *b, int l)
{
    for (int i = 0; i < l; ++i)
        if (a[i] != b[i]) return false;
    return true;
}

int main()
{
    char word[12];
    char buffer[12];

    // read word
    scanf("%s", word);
    int wl = strlen(word);  // length of word
    for (int i = 0; i < wl; ++i)
        word[i] = tolower(word[i]);
    
    // clear '\n';
    char c;
    while ((c = getchar()) && c != '\n');

    // read article
    int i = 0, j = 0;   // i for buffer, j for article
    int count = 0, pos = -1;   // counter and first position;
    while ((c = getchar()) != EOF)
    {
        // printf("%c %d %d\n", c, i, j);
        if (isalpha(c))
        {
            if (i < wl)
                buffer[i] = tolower(c);
            ++i;
        }
        else
        {
            if (i == wl && compare(buffer, word, wl))
            {
                count++;
                if (pos == -1) pos = j - wl;
            }
            i = 0;
        }
        ++j;
    }

    if (count == 0)
        printf("-1");
    else
        printf("%d %d", count, pos);
}
