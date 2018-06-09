#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;


const int maxn = 35;
int f[maxn][maxn];
int solve(int n)
{
    if(n & 1) return 0;
    if(f[n][0]) return f[n][0];
    f[0][0] = f[0][1] = f[0][2] = 1; //3 * 0的矩形,用1*2的方块填充有1中方法.
    f[1][0] = 0; //3 * 1的矩形, 用1*2的方块填充, 0中方法.
    f[1][1] = 1;
    f[1][2] = 1;

    for(int i=2; i<=n; ++i)
    {
        f[i][0] = (i & 1 ? 0 : f[i-2][0] + f[i-2][2] + f[i-1][1] );
        f[i][1] = f[i-1][2];
        f[i][2] = f[i][0] + f[i-1][1];
    }
    return f[n][0];
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int n;
    while(scanf("%d",&n) && n >= 0) printf("%d\n",solve(n));

    return 0;
}