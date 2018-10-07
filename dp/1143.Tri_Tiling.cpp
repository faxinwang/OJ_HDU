/*
Tri Tiling
Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)

Problem Description
In how many ways can you tile a 3xn rectangle with 2x1 dominoes? Here is a sample tiling of a 
3x12 rectangle.

Input
Input consists of several test cases followed by a line containing -1. Each test case is a line 
containing an integer 0 ≤ n ≤ 30. 
 

Output
For each test case, output one integer number giving the number of possible tilings. 
 

Sample Input
2
8
12
-1


Sample Output
3
153
2131

解题思路:
状态定义:
f[i][0]表示3行i列, 多出0个格子时的方案数, 显然当i为奇数时, 3*i也是奇数, 不可能用2*1的方块填充满,情况属为0
f[i][1]表示3行i列, 多出1个格子时的方案数
f[i][2]表示3行i列, 多出2个格子时的方案数

状态转移方程:
f[i][0] = (i & 1 ? 0 : f[i-2][0] + f[i-2][2] + f[i-1][1] );
f[i][1] = f[i-1][2];
f[i][2] = f[i][0] + f[i-1][1];

*/
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;

const int maxn = 35;
int f[maxn][3];

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