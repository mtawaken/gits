
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

#define maxn 106
ofstream fout;
struct Device
{
    int p, b;
} dev[maxn][maxn];

int s, e, n;
int maxb[maxn], minb[maxn], num[maxn];

void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
        for (int j = 0; j < num[i]; j++)
            scanf("%d%d", &dev[i][j].b, &dev[i][j].p);
    }
}

int find(int b)
{
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        int minp = 0x3f3f3f3f;
        for (int j = 0; j < num[i]; j++)
            if (dev[i][j].b >= b)
                minp = min(minp, dev[i][j].p);
        ret += minp;
    }
    return ret;
}

void work()
{
    for (int i = 0; i < n; i++)
    {
        minb[i] = maxb[i] = dev[i][0].b;
        for (int j = 1; j < num[i]; j++)
        {
            maxb[i] = max(maxb[i], dev[i][j].b);
            minb[i] = min(minb[i], dev[i][j].b);
        }
    }
    s = minb[0];
    e = maxb[0];
    for (int i = 1; i < n; i++)
    {
        s = min(s, minb[i]);
        e = min(e, maxb[i]);
    }
    fout<<s<<" "<<e<<endl;
    double ans = 0;
    for (int i = s; i <= e; i++)
    {
        int d = find(i);
        ans = max(ans, i * 1.0 / d);
    }
    printf("%.3f\n", ans);
}

int main()
{
    //freopen("t.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    fout.open("test1");
    while (t--)
    {
        input();
        work();
    }
    return 0;
}
