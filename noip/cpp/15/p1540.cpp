// P1540 机器翻译
// https://www.luogu.org/problemnew/show/P1540

#include <iostream>

using namespace std;

#define MAX_N 1001
#define MAX_M 101

int main()
{
    int mq[MAX_M];   // memory queue for word
    bool dict[MAX_N] = {false}; // dict for word, if word in memory
    int m, n; // m for memory size, n for num of words
    cin >> m >> n;

    int i = 0;    // counter of words
    int j = 0;    // counter of words in memory
    int word;
    int lookup = 0; // counter of lookup

    for (i = 0; i < n; ++i)
    {
        cin >> word;
        if (!dict[word])
        {
            lookup++;
            dict[word] = true;
            if (j >= m)
                dict[mq[j % m]] = false; // remove word
            mq[j++ % m] = word;
        } 
    }
    cout << lookup;
}