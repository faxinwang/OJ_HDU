/*
Problem Description
Arcueid likes nya number very much.
A nya number is the number which has exactly X fours and Y sevens(If X=2 and Y=3 , 172441277 and 
47770142 are nya numbers.But 14777 is not a nya number ,because it has only 1 four).
Now, Arcueid wants to know the K-th nya number which is greater than P and not greater than Q.
 

Input
The first line contains a positive integer T (T<=100), indicates there are T test cases.
The second line contains 4 non-negative integers: P,Q,X and Y separated by spaces.
( 0<=X+Y<=20 , 0< P<=Q <2^63)
The third line contains an integer N(1<=N<=100).
Then here comes N queries.
Each of them contains an integer K_i (0<K_i <2^63).
 

Output
For each test case, display its case number and then print N lines.
For each query, output a line contains an integer number, representing the K_i-th nya number in (P,Q].
If there is no such number,please output "Nya!"(without the quotes).
 

Sample Input
1
38 400 1 1
10
1
2
3
4
5
6
7
8
9
10
 

Sample Output
Case #1:
47
74
147
174
247
274
347
374
Nya!
Nya!


题目大意：
定义nya数为数字中4的个数n4==X,且7的个数n7==Y的数,X,Y的值由输入数据确定。
求在给定的区间(P,Q]内的第k个nya数。

解题思路：
1.首先用数位dp求[0,n]区间内的nya数字的个数：
  dp[len][n4][n7] 表示长度为len,包含n4个4和n7个7的数字的个数。
2.求(P,Q]区间内的第k个nya数，用二分搜索，确定 base = 区间[0,P]内的nya数字的个数。
  然后通过二分搜索 solve(mid) - base == K，如果找到了这样的mid，则mid就是答案，
  否则不存在符合要求的数字。
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn = 25;

int T,N,X,Y;
int bits[maxn];
LL P,Q,K;
LL dp[maxn][maxn][maxn];

LL dfs(int len, int n4, int n7, bool limit)
{
    // printf("len=%d n4=%d n7=%d\n",len,n4,n7);
    if(len <= 0) return n4==X && n7==Y;
    if(!limit && ~dp[len][n4][n7]) return dp[len][n4][n7];
    int up = limit? bits[len-1] : 9;
    LL ans = 0;
    for(int i=0; i<=up; ++i)
    {
        int _n4 = n4;
        int _n7 = n7;
        if(n4 == X && i == 4) continue; //n4的个数>X， 后面的数字肯定都不符合要求
        if(n7 == Y && i == 7) continue; //n7的个数>Y， 后面的数字肯定都不符合要求
        if(i==4) ++_n4;
        if(i==7) ++_n7;
        ans += dfs( len-1, _n4, _n7, limit && i==up);
    }
    return limit? ans : dp[len][n4][n7] = ans;
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
    return dfs(len, 0, 0, true);
}

LL binSearch(LL K)
{
    LL L=P+1, R=Q, ans=0, mid;
    LL base = solve(P);
    while(L < R)
    {
        // mid = L + (R - L)>>1; //刚开始这样写，死循环了半天才发现是这里的问题，二分的坑真多。
        mid = L + (R - L) / 2; 
        if( solve(mid) - base >= K )
        {
            ans = mid;
            R = mid; //mid值可能是答案，所以令 R=mid
        }else L = mid+1; //mid值不可能是答案，所以令L=mid+1
    }
    return ans;
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int kiss=0;
    cin>>T;
    while(T--)
    {
        cin>>P>>Q>>X>>Y;
        cin>>N;
        memset(dp,-1,sizeof(dp)); //初始化放在最外面会WA,要放进来才可以。
        printf("Case #%d:\n",++kiss);
        for(int i=0; i<N; ++i)
        {
            cin>>K;
            LL ans = binSearch(K);
            if(ans) cout<<ans<<endl;
            else cout<<"Nya!"<<endl;
        }
    }

    return 0;
}