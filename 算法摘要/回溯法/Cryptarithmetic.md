
### Cryptarithmetic puzzles

参考

- [Verbal arithmetic](https://en.wikipedia.org/wiki/Verbal_arithmetic)
- [Solving Cryptarithmetic puzzles]( https://www.geeksforgeeks.org/backtracking-set-8-solving-cryptarithmetic-puzzles/)

```
  SEND
+ MORE
------
 MONEY
```

破解诸如上面的计算式，每个字母代表一个数字。字母、数字一一对应。

问题可以有不同的扩展：

1. 非10进制加法
2. 乘法运算

#### 常规方法： 回溯法

一种常规思路是遍历所有的数字排列（对应字母顺序），代入运算表达式，看是否匹配等式。

但是很不幸的是， $N$个字母的问题，有 $N!$ 种排列 。大概 $10! \sim 10^6$，还可以接受； $15! \sim 10^{12}$ 这就有点过分了。 $20! \sim 10^{18}$ 已经基本上算不完了。

这就需要一些剪枝、回溯策略

- 从等式最右侧开始， carry 为 0。
- 如果已经超出最左侧， 看 carry 是否为 0。 如果是说明全部计算正确，返回 true； 否则返回 false
- 如果是上半部分的字符（非最后的结果字串）
    - 如果字符已经赋值了，递归搜索
    - 对每一个未使用过的数字，赋值给字符，递归搜索及回溯
- 如果是最后的和：
    - 如果字符已赋值，并且等于计算的 sum，递归搜索
    - 如果字符已赋值，但是不等于计算的 sum， 返回 false
    - 如果字符未赋值，但是 sum 数字已经被使用， 返回 false
    - 其他情况（字符未赋值，sum数字未使用）， 将 sum 数字赋值给字符， 递归搜索回溯。
- 以上情况都没有返回 true或 false， 返回 false。

上面回溯法的一个关键点是： 区分上半部分和下半部分：上半部分搜索；下半部分直接使用 sum 结果（就避免了再去找可用数字）。相当于在每一个数位，搜索 $N^2$ 次。


对于洛谷 P1092 问题，按照回溯法写了一个，在$n < 16$ 情况下，表现还可以。但是到了 $n = 20$ 的时候，计算就有点慢了。

尝试了以下几种优化策略：

1. 在上半部选择未使用的数字时，从 $n - 1$ 到 $0$ 逆序查找。 这可以提高一些测试点数据的计算速度（54s -> 2s），但这只是针对个别数据，感觉上并不是通用的。
2. 提前检查剪枝策略。
    - 字符数有 $n$ 个， 但是表达式中总共有 $n * 3$ 个。考虑到在末尾给一些字符赋值，可能在很久之后才发现到错误，在递归到每列的时候，提前检查一下这些赋值在后面是否有效。
    - 检查的点有两个，一个是对每一列：  `(a + b) % n == c || (a + b + 1) % n == c`。 另一个是最高位没有进位，因此检查 `a + b >= n` 是错误的。

使用第二个剪枝策略之后，可以大大优化计算速度。

```cpp
// P1092 虫食算
// https://www.luogu.org/problemnew/show/P1092

#include <cstdio>

const int MAX_N = 30;
int n;
char s[4][MAX_N];
bool used[MAX_N] = { false };    // mark used
int v[MAX_N] = { -1 };   // value of A,B,C .... Z

bool check_valid(int col)
{
    int a, b, c;
    for (int j = n - col - 1; j >= 0; --j)
    {
        a = v[s[0][j]];
        b = v[s[1][j]];
        c = v[s[2][j]];
        if (a == -1 || b == -1 || c == -1) continue;

        if ((a + b) % n != c && (a + b + 1) % n != c)
            return false;
    }
    return !(a + b >= n);
}

bool solve(int r, int c, int sum)
{
    if (c == n)
    {
        // print_solution();
        return sum == 0;
    }
    if (!r && !check_valid(c))
    {
        return false;
    }
    int j = n - c - 1;
    int ch = s[r][j];
    int x = v[ch];
    if (r < 2)  // rows
    {
        if (x != -1) // assigned
            return solve(r + 1, c, sum + x);

        for (int z = n - 1; z >= 0; --z)
        {
            if (!used[z])
            {
                v[ch] = z;
                used[z] = true;
                if (solve(r + 1, c, sum + z))
                    return true;
                used[z] = false;
                v[ch] = -1;
            }
        }
    }
    else  // row of sum
    {
        int d = sum % n;
        if (x == d)    // assigned and match
            return solve(0, c + 1, sum / n);
        if (x != -1 && x != d)  // assigned and not match
            return false;
        if (x == -1 && used[d]) // not assigned and digit used
            return false;

        v[ch] = d;
        used[d] = true;
        if (solve(0, c + 1, sum / n)) return true;
        used[d] = false;
        v[ch] = -1;
        return false;
    }
    return false;
}

int main()
{
    scanf("%d", &n);
    scanf("%s\n%s\n%s", s[0], s[1], s[2]);

    for (int i = n - 1, j = 0; i >= 0; --i)
    {
        v[i] = -1;
        used[i] = false;
        for (int r = 0; r < 3; ++r)
            s[r][i] -= 'A';
    }

    solve(0, 0, 0);

    for (int i = 0; i < n; ++i)
        printf("%d ", v[i]);

    return 0;
}
```
