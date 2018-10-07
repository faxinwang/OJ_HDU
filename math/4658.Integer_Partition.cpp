/*
Integer Partition
Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)


Problem Description
Given n, k, calculate the number of different (unordered) partitions of n such that no part 
is repeated k or more times. 
 

Input
First line, number of test cases, T. 
Following are T lines. Each line contains two numbers, n and k. 

1<=n,k,T<=105
 

Output
T lines, each line contains answer to the responding test case. 
Since the numbers can be very large, you should output them modulo 109+7.
 

Sample Input
4
4 2
4 3
4 4
4 5
 

Sample Output
2
4
4
5
 

Source
2013 Multi-University Training Contest 6
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e5+5;
const int mod = 1000000007;
typedef long long LL;
int p[maxn];

inline LL five(LL n){ return (3*n*n-n)/2; } //计算第n个五边形数

void init_p()
{
    p[0] = 1;
    for(int i=1; i<maxn; ++i)
    {
        for(int j=1,s=1; ; ++j, s=-s)
        {
            LL c = five(j);
            if(i - c < 0) break;
            p[i] += p[i - c] * s;
            if(p[i] >= mod ) p[i] -= mod;
            if(p[i] < 0) p[i] += mod;

            c = five(-j);
            if(i - c < 0) break;
            p[i] += p[i - c] * s;
            if(p[i] >= mod ) p[i] -= mod;
            if(p[i] < 0) p[i] += mod;
        }
    }
}

int solve(int n, int k)
{
    int ans = p[n];
    for(int j=1, s=-1; ; ++j, s=-s)
    {
        LL c = five(j);
        if(n - k * c < 0) break;
        ans += p[n - k * c] * s;
        if(ans >= mod) ans -= mod;
        if(ans < 0) ans += mod;
        
        c = five(-j);
        if(n - k * c < 0) break;
        ans += p[n - k * c] * s;
        if(ans >= mod) ans -= mod;
        if(ans < 0) ans += mod;
        
    }
    return ans;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    init_p();
    int T,n ,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d", &n,&k);
        printf("%d\n",solve(n,k));
    }

    return 0;
}