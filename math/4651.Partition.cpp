/*
Partition
Time Limit: 6000/3000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)


Problem Description
How many ways can the numbers 1 to 15 be added together to make 15? The technical term for what you 
are asking is the "number of partition" which is often called P(n). A partition of n is a collection 
of positive integers (not necessarily distinct) whose sum equals n.

Now, I will give you a number n, and please tell me P(n) mod 1000000007.
 

Input
The first line contains a number T(1 ≤ T ≤ 100), which is the number of the case number. The next T 
lines, each line contains a number n(1 ≤ n ≤ 105) you need to consider.

 

Output
For each n, output P(n) in a single line.
 

Sample Input
4
5
11
15
19
 

Sample Output
7
56
176
490
 

Source
2013 Multi-University Training Contest 5


参考:
https://blog.csdn.net/zhoufenqin/article/details/9821617

*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e5+5;
const int mod = 1000000007;
typedef long long LL;
int p[maxn];

inline LL five(LL n){ return (3*n*n-n)/2; } //计算第n个五边形数

void init_p() //五边形数打表
{
    p[0]=1;
    for(int i=1; i<maxn; ++i)
    {
        for(int j=1, s=1; ; ++j, s=-s)
        {
            LL k = five(j);
            if(i - k < 0) break;
            p[i] += p[i - k] * s;
            if(p[i] >= mod )p[i] %= mod;
            if(p[i] < 0) p[i] += mod;

            k = five(-j);
            if(i - k < 0) break;
            p[i] += p[i - k] * s;
            if(p[i] >= mod ) p[i] %= mod;
            if(p[i] < 0) p[i] += mod;
        }
    }
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    init_p();

    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d\n", p[n]);
    }

    return 0;
}