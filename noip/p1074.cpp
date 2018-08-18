// P1074 靶形数独
// https://www.luogu.org/problemnew/show/P1074

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 9
#define NN 81

const int MAX_STATE = 1 << N;
const int INIT_STATE = (1 << N) - 1;

int grid[NN];
int row[N], col[N], box[N];
int spiral[NN];
int available[NN];
int score[NN];     // fixed
int box_index[NN]; // fixed
int msb[MAX_STATE];  // most significant bit

int max_sum = -1;

bool cmp_available(const int a, const int b)
{
    return available[a] < available[b];
    // return available[spiral[a]] < available[spiral[b]];
    // if (available[a] != available[b])
    //     return available[a] < available[b];
    // return score[a] > score[b];
}

bool cmp_center_distance(const int a, const int b)
{
    int ax = a / N, ay = a % N;
    int bx = b / N, by = b % N;
    // the smaller, the farther from center
    return min(min(ax, N - 1 - ax), min(ay, N - 1 - ay)) > min(min(bx, N - 1 - bx), min(by, N - 1 - by));
}

bool cmp2(const int a, const int b)
{
    int ax = a / N, ay = a % N;
    int bx = b / N, by = b % N;
    // the smaller, the farther from center
    int da = min(min(ax, N - 1 - ax), min(ay, N - 1 - ay));
    int db = min(min(bx, N - 1 - bx), min(by, N - 1 - by));
    if (da == 0) return false;
    if (db == 0) return true;
    return available[a] < available[b];
}


void print_grid()
{
    for (int i = 0; i < 9; i++, putchar('\n'))
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", grid[i * N + j]);
    }
}

int sc = 0;
void search(int k, int sum)
{
    ++sc;
    // if (k == 49 && sum <= max_sum) return;
    while (k < NN && grid[spiral[k]] != 0) ++k;
    if (k == NN)
    {
        if (sum > max_sum)
        {
            max_sum = sum;
            // print_grid();
            // printf("%d\n", max_sum);
        }
        // max_sum = sum;
        return;
    }

    int kk = spiral[k];
    int r = kk / N, c = kk % N, b = box_index[kk];
    int state = row[r] & col[c] & box[b], num, mask;
    while (state)
    {
        num = msb[state];
        mask = 1 << (num - 1);
        row[r] ^= mask;
        col[c] ^= mask;
        box[b] ^= mask;
        search(k + 1, sum + num * score[kk]);
        // if (max_sum != -1) return;
        row[r] ^= mask;
        col[c] ^= mask;
        box[b] ^= mask;
        state -= mask;
    }
}

int main()
{
    int i, j, t, k;
    int sum = 0;
    int raw_score[] = {0, 1, 2, 3, 4};

    for (i = 0; i < N; ++i)
        row[i] = col[i] = box[i] = INIT_STATE;

    for (k = i = 0; i < N; ++i)
        for (j = 0; j < N; ++j, ++k)
        {
            scanf("%d", &t);
            grid[k] = t;
            spiral[k] = k;
            score[k] = raw_score[min(min(i, N - 1 - i), min(j, N - 1 - j))];
            box_index[k] = i / 3 * 3 + j / 3;
            if (t)
            {
                sum += t * score[k];
                --t;
                row[i] &= (INIT_STATE - (1 << t));
                col[j] &= (INIT_STATE - (1 << t));
                box[box_index[k]] &= (INIT_STATE - (1 << t));
            }
        }
    
    msb[0] = 0;
    for (i = 1; i < MAX_STATE; ++i)
    {
        msb[i] = msb[i - 1] + (1 << msb[i - 1] == i);
        // printf("%d, %x, %d\n", i, i, msb[i]);
    }

    // statistic available
    int state;
    for (k = i = 0; i < N; ++i)
        for (j = 0; j < N; ++j, ++k)
        {
            available[k] = 0;
            if (!grid[k])
            {
                // state = row[i] & col[j] & box[box_index[k]];
                state = row[i];
                for (; state; state >>= 1)
                    available[k] += (state & 1);
                available[k] <<= 4;
                state = col[j];
                for (; state; state >>= 1)
                    available[k] += (state & 1);
                available[k] <<= 4;
                state = box[box_index[k]];
                for (; state; state >>= 1)
                    available[k] += (state & 1);
            }
        }
    sort(spiral, spiral + NN, cmp_available);

    // sort(spiral, spiral + NN, cmp_center_distance);
    // sort(spiral, spiral + 49, cmp_available);
    // sort(spiral + 49, spiral + NN, cmp_available);

    // for (k = 0; k < NN; ++k)
    //     printf("%3d", spiral[k]);
    // printf("\n");
    // for (k = 0; k < NN; ++k)
    //     printf("%3d", grid[spiral[k]]);
    // printf("\n");
    // for (k = 0; k < NN; ++k)
    //     printf("%3d", available[spiral[k]]);
    // printf("\n");

    k = 0;
    while (available[spiral[k]] == 0) ++k;

    search(k, sum);
    // printf("%d\n", max_sum);
    printf("%d\n", max_sum + 2430);  // 2430 = 45 * 9 * 6;
    // printf("%d\n", sc);
    return 0;
    

    // // spiral
    // int rs = 0, re = N - 1, cs = 0, ce = N - 1;
    // while (rs <= re && cs <= ce)
    // {
    //     i = rs;
    //     for (j = cs; j < ce; ++j)
    //         spiral[k++] = i * N + j;
    //     for (; i < re; ++i)
    //         spiral[k++] = i * N + j;
    //     for (; j > cs; --j)
    //         spiral[k++] = i * N + j;
    //     for (; i > rs; --i)
    //         spiral[k++] = i * N + j;
    //     ++rs, ++cs, --re, --ce;
    // }
    // if (k < NN) spiral[k] = i * N + j;

    // for (i = 0; i < NN; ++i)
    //     printf("%d ", spiral[i]);
    // printf("\n");
    // for (i = 0; i < N; ++i, putchar('\n'))
    //     for(j = 0; j < N; ++j)
    //         printf("%3d", i * N + j);
    // printf("\n");

}