/*
Problem Description
A wqb-number, or B-number for short, is a non-negative integer whose decimal form contains 
the sub- string "13" and can be divided by 13. For example, 130 and 2613 are wqb-numbers, 
but 143 and 2639 are not. Your task is to calculate how many wqb-numbers from 1 to n for a 
given integer n.
 

Input
Process till EOF. In each line, there is one positive integer n(1 <= n <= 1000000000).
 

Output
Print each answer in a single line.
 

Sample Input
13
100
200
1000
 

Sample Output
1
1
2
2

题目大意：
给定正整数N, 求从1到N中有多少个数字既包含子串13又可以被13整除。

解题意思：
dp[len][mod][state]表示长度为len的数字，模13得mod，且状态为state时所包含的合法数字的个数。
state取值如下：
0: 表示数字中不含13且末尾不是1
1：表示数字中不含13且末尾是1
2： 表示数字中包含13

*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int bits[15];
int dp[15][15][3];

int dfs(int len, int mod, int state, bool limit)
{
    // if(len == 0) return (!has13) || (mod % 13 != 0);
    if(len == 0) return state==2 && mod == 0;
    if(!limit && ~dp[len][mod][state]) return dp[len][mod][state];
    int up = limit? bits[len-1] : 9;
    int cnt = 0, _state;
    for(int i=0; i<=up; ++i)
    {
        _state = state;
        if(state == 0 && i == 1) _state = 1; //末尾是1
        if(state == 1 && i != 1) _state = 0; //末尾不是1
        if(state == 1 && i == 3) _state = 2; //有13
        cnt += dfs(len-1, (mod*10+i)%13,  _state, limit && i==up );
    }
    return limit? cnt : dp[len][mod][state] = cnt;
}

int solve(int N)
{
    int len = 0, n = N;
    while(n)
    {
        bits[len++] = n % 10;
        n /= 10;
    }
    bits[len] = 0;
    return dfs(len, 0, 0, true);
}


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    memset(dp,-1,sizeof(dp));
    int n;
    while(~scanf("%d",&n)) cout<<solve(n)<<endl;

    return 0;
}
