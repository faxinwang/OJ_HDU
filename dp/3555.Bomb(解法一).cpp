/*
Problem Description
The counter-terrorists found a time bomb in the dust. But this time the terrorists improve 
on the time bomb. The number sequence of the time bomb counts from 1 to N. If the current 
number sequence includes the sub-sequence "49", the power of the blast would add one point.

Now the counter-terrorist knows the number N. They want to know the final points of the power. 
Can you help them?
 

Input
The first line of input consists of an integer T (1 <= T <= 10000), indicating the number of 
test cases. For each test case, there will be an integer N (1 <= N <= 2^63-1) as the description.

The input terminates by end of file marker.
 

Output
For each test case, output an integer indicating the final points of the power.
 

Sample Input
3
1
50
500
 

Sample Output
0
1
15

Hint
From 1 to 500, the numbers that include the sub-sequence "49" are 
"49","149","249","349","449","490","491","492","493","494","495","496","497","498","499",
so the cntwer is 15.

题目大意：
给定正整数N,求从0到N中包含子串49的数字的个数。

解题思路：（直接法）
dp[len][is4] 表示长度为len位，且上一位为4的状态下，从0到10^(len)中包含49的数字的个数
dfs参数中除必须的len，limit外，只需要一个is4记录上一位是否为4，
如果上一位为4，并且当前位为9
    如果当前数字达到上限，则 cnt = N % 10^(len-1) + 1 (例如：N=4956，则4900到4956有 4900,4901,4902,...,4956一共57个)
    否则 cnt = 10^(len-1)   (例如： 490 到 500有 490, 491, 492,...,499一共10个)
否则，长度为len, 上一位不是4的状态中符合条件的数字个数应从更短的数中累加而来。
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;

LL dp[65][2];
LL base[20], bits[20], N;

//当前第几个数位(从高位到低位)， 上一位是否为4，是否是上限
LL dfs(int len, bool is4, bool limit)
{
    if(len == 0) return 0;
    if(!limit && ~dp[len][is4]) return dp[len][is4];
    int up = limit? bits[len-1] : 9;
    LL cnt = 0;
    for(int i=0; i<=up; ++i)
    {
        if(is4 && i==9)
            cnt += limit? N % base[len-1] + 1 : base[len-1];
        else
            cnt += dfs(len-1, i==4, limit && i==up);
    }
    return limit? cnt : dp[len][is4] = cnt;
}

LL solve(LL n)
{
    int len = 0;
    while(n)
    {
        bits[len++] = n % 10;
        n /= 10;
    }
    bits[len] = 0;
    return dfs(len, false, true );
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    LL T;
    base[0] = 1;
    for(int i=1; i<20; ++i) base[i] = base[i-1] * 10;
    memset(dp,-1,sizeof(dp));

    cin>>T;
    while(T--)
    {
        cin>>N;
        cout<<solve(N)<<endl;
    }
    return 0;
}