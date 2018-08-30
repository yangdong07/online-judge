// P1019 单词接龙
// https://www.luogu.org/problemnew/show/P1019

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 21;

int n;
string s[MAX_N];
int match[MAX_N][MAX_N];
int used[MAX_N] = { 0 };
int max_len = 0;

int concate(const string &s1, const string &s2)
{
    int l1 = s1.size();
    int l2 = s2.size();

    int i0 = l1 < l2 ? 0 : l1 - l2;  // i 的起点位置
    int j;

    // 反序以保证最小重叠部分
    for (int i = l1 - 1; i > i0; --i)
    {
        for (j = 0; j < l1 - i; ++j)
            if (s1[i + j] != s2[j])
                break;
        if (j == l1 - i)
            return j;
    }
    return 0;
}

void init_match()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            match[i][j] = concate(s[i], s[j]);

    // for (int i = 0; i < n; ++i)
    //     for (int j = 0; j < n; ++j)
    //         cout << s[i] << " " << s[j] << " " << match[i][j] << endl;
}

// int idx[MAX_N];
void dfs(int last, int len) //, int d)
{
    bool no_more = true;
    // idx[d] = last;
    for (int i = 0; i < n; ++i)
    {
        if (used[i] < 2 && match[last][i])
        {
            no_more = false;
            used[i]++;
            dfs(i, len + s[i].size() - match[last][i]);
            used[i]--;
        }
    }
    if (no_more)
    {
        // cout << len << ": ";
        // for (int i = 0; i <= d; ++i)
        //     cout << s[idx[i]] << " ";
        // cout << endl;
        max_len = max(len, max_len);
    }
}

int main()
{
    char c;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    cin >> c;

    init_match();

    for (int i = 0; i < n; ++i)
    {
        if (c == s[i][0])
        {
            used[i]++;
            dfs(i, s[i].size());
            used[i]--;
        }
    }

    cout << max_len << endl;

    return 0;
}