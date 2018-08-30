// P3955 图书管理员
// https://www.luogu.org/problemnew/show/P3955

#include <cstdio>
#include <cstring>

int main()
{
    const int MAX_L = 5;
    const int MAX_N = 1001;  // 最长4位编码
    int n, q, i, j;
    scanf("%d %d", &n, &q);

    int index[MAX_L][MAX_N];
    for (i = 0; i < n; ++i)
        for (j = 0; j < MAX_L; ++j)
            index[j][i] = -1;

    int base;
    int id, _id;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &id);
        printf("%d\n", id);
        for (j = 1, base = 10; j < MAX_L && base < MAX_N; ++j)
        {
            _id = index[j][id % base];
            printf("%d %d %d\n", j, id % base, base);
            if (_id == -1 || id < _id)
                index[j][id % base] = id;
            base *= 10;
        }
    }

    int len, code, t;
    for (j = 0; j < q; ++j)
    {
        scanf("%d %d", &len, &code);
        for (base = 1, t = len; t; --t, base *= 10);
        printf("%d %d %d\n", len, code, code % base);
        // printf("%d\n", index[len][code % base]);
    }

    return 0;
}

// int main()
// {
//     const int MAX_INT = 1 << 30;
//     const int MAX_N = 1001;  // 最多1000本书
//     int n, q, i, j;
//     scanf("%d %d", &n, &q);

//     int book[MAX_N];
//     for (i = 0; i < n; ++i)
//         scanf("%d", &book[i]);

//     int code, len, base, min_id;
//     for (j = 0; j < q; ++j)
//     {
//         scanf("%d %d", &len, &code);
//         for (base = 1; len; --len, base *= 10);
//         min_id = MAX_INT;
//         for (i = 0; i < n; ++i)
//             if (book[i] % base == code)
//                 min_id = min(min_id, book[i]);
//         printf("%d\n", min_id == MAX_INT ? -1 : min_id);
//     }

//     return 0;
// }