// P2369 EXCEEDED WARNING A
// https://www.luogu.org/problemnew/show/P2369


#include <cstdio>

#define MAX_N 100001

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b; *b = t;
}

void insert_heap(int heap[], int num, int size)
{
    int k = size + 1;
    heap[k] = num;
    // swim up
    while (k > 1 && heap[k/2] < heap[k])
    {
        swap(&heap[k/2], &heap[k]);
        k /= 2;
    }
}

void sink(int heap[], int k, int size)
{
    int j;
    while (2 * k <= size)
    {
        j = 2 * k;
        if (j < size && heap[j] < heap[j + 1])
            ++j;
        if (heap[k] < heap[j])
            swap(&heap[k], &heap[j]);
        else
            break;
        k = j;
    }
}

int pop_heap(int heap[], int size)
{
    int num = heap[1];
    heap[1] = heap[size];

    // sink down
    sink(heap, 1, size - 1);

    return num;
}

void sort_heap(int heap[], int size)
{
    int num, k = size;
    while (k)
    {
        num = pop_heap(heap, k);
        heap[k--] = num;
    }
}

int main()
{
    int heap[MAX_N] = { 0 };
    int n, m, i;
    scanf("%d %d", &n, &m);

    int number;

    for (i = 0; i < m; ++i)
    {
        scanf("%d", &number);
        insert_heap(heap, number, i);
    }

    for ( ; i < n; ++i)
    {
        scanf("%d", &number);
        if (number < heap[1])
        {
            heap[1] = number;
            sink(heap, 1, m);
        }
    }

    sort_heap(heap, m);
    for (i = 1; i <= m; ++i)
        printf("%d\n", heap[i]);
}
