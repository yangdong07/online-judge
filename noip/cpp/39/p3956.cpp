// P3956 棋盘
// https://www.luogu.org/problemnew/show/P3956

#include <cstdio>
#include <queue>

using namespace std;

const int INF = 0x1fffffff;
const int MAX_N = 100 + 1;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int weight[4][4] = {{INF, 0, 1, INF},
                    {2, 0, 1, 3},
                    {3, 1, 0, 2},
                    {INF, 1, 0, INF}};

// const int MAX_N = 1000;

int n;
int map[MAX_N][MAX_N] = {0};
int cost[MAX_N][MAX_N][4] = {0};

struct vertex 
{
    int x, y, color, spe;
    vertex(int x, int y, int c, int spe) : x(x), y(y), color(c), spe(spe) {}
    bool operator<(const vertex &rhs) const
    {
        return spe > rhs.spe;   // min first, max last
    }
};


void dijkstra(int x, int y, int color)
{
    int i, j, k, w;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            for (k = 0; k < 4; ++k)
                cost[i][j][k] = INF;

    priority_queue<vertex> pq;
    cost[x][y][color] = 0; 
    pq.push(vertex(x, y, color, 0));

    while (!pq.empty())
    {
        vertex v = pq.top();
        pq.pop();
        if (v.spe > cost[v.x][v.y][v.color]) continue;
        for (i = 0; i < 4; ++i)
        {
            int xx = v.x + dx[i], yy = v.y + dy[i];
            if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
            for (k = 0; k < 4; ++k)
            {
                if ((map[xx][yy] && k == map[xx][yy])
                    || (!map[xx][yy] && (k == 0 || k == 3)))
                {
                    w = weight[v.color][k];
                    if (v.spe + w < cost[xx][yy][k])
                    {
                        cost[xx][yy][k] = v.spe + w;
                        pq.push(vertex(xx, yy, k, v.spe + w));
                    }
                }
            }
        }
    }
}


int main()
{
    int m, i, j, k, color;
    scanf("%d %d", &n, &m);

    for (k = 0; k < m; ++k)
    {
        scanf("%d %d %d", &i, &j, &color);
        map[i][j] = color + 1;   // 1 red, 2 yellow
    }

    dijkstra(1, 1, map[1][1]);

    int answer = INF;
    for (k = 0; k < 4; ++k)
        if (cost[n][n][k] < answer)
            answer = cost[n][n][k];
    
    printf("%d\n", answer == INF ? -1 : answer);
    // for (i = 1; i <= n; ++i)
    // {
    //     for (j = 1; j <= n; ++j)
    //     {
    //         for (k = 0; k < 4; ++k)
    //             printf("%-3d", cost[i][j][k] == INF ? -1 : cost[i][j][k]);
    //         printf("\t");
    //     }
    //     printf("\n");
    // }

    return 0;
}