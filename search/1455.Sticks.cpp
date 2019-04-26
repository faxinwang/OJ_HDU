/*
Sticks
Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)

Problem Description
George took sticks of the same length and cut them randomly until all parts became at most 
50 units long. Now he wants to return sticks to the original state, but he forgot how many 
sticks he had originally and how long they were originally. Please help him and design a 
program which computes the smallest possible original length of those sticks. All lengths 
expressed in units are integers greater than zero. 


Input
The input contains blocks of 2 lines. The first line contains the number of sticks parts 
after cutting, there are at most 64 sticks. The second line contains the lengths of those 
parts separated by the space. The last line of the file contains zero.


Output
The output file contains the smallest possible length of original sticks, one per line. 


Sample Input
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0


Sample Output
6
5


题目大意：
有一堆长度在[1,n]之间的木棒，他们是由若干根长度为 L 的木棒截断而成的，求最小的 L.

解题思路：
1. 首先确定L可取值的范围，定义maxLen为这些木棒中最大长度, sumLen为这些木棒的长度和，
    则显然 maxLen <= L <= sumLen
2. 由于题目要求最小的L，因此直接从maxLen到sumLen对L进行枚举，注意当 sumLen不能被 L 整除时，
    说明 m 不是整数，这是不合理的，因此要忽略掉这样的 L.
3. 对于给定长度的 L, 我们要判断这一堆木棒是否可能由 m=sumLen/L 根长度为 L 的木棒截断而成。也就是要
    判断能否将这一堆木棒分成 m 组，每一组的木棒长度之和为 L. 如果可以，则每一根木棒必定可以被分到
    某一组，否则只能说明 L 不合适。
4. 在判断给定的 L 是否可行时，m的值是固定的，但拼接成长度为L所需要的木棒的数目是不固定的，因此难以使用
    循环的方式进行暴力求解。注意到每一根木棒在挑选时要么选要么不选，因此这是一个搜索问题，可以用dfs来进行求解。
*/


#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 65;

int a[maxn], n;
bool vis[maxn];
//dfs global variable
int Original_Len, Original_Num;

bool dfs(int k, int curLen, int cnt)
{
    if(cnt == Original_Num) return true;
    if(curLen == Original_Len ) return dfs(0, 0, cnt+1);
    for(int i = k; i<n; ++i)
    {
        if(!vis[i] && curLen + a[i] <= Original_Len){
            vis[i] = 1; //选择第 i 根木棒
            if( dfs(i+1, curLen + a[i], cnt) ) return true;
            vis[i] = 0; //不选择第 i 根木棒
            if(curLen == 0) return false; //curLen为 0 表示第 i 根木棒无法跟任何其他的木棒组合出长度L (优化二)
            // while(i+1<n && a[i] == a[i+1]) ++i;  //需要排序  (优化三, 不用也可以通过)
        }
    }
    return false;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r", stdin);
    #endif
    
    while(scanf("%d",&n) && n)
    {
        int sumLen = 0, maxLen=0;
        fill(vis, vis+maxn, 0);

        for(int i=0; i<n; ++i)
        {
            scanf("%d", a+i);
            sumLen += a[i];
            maxLen = max(maxLen, a[i]);
        }

        // sort(a, a+n, greater<int>()); 
        // sort(a,a+n);

        // for(int Len = a[n-1]; Len<=sumLen; ++Len)
        for(int Len=maxLen; Len <= sumLen; ++Len)
        {
            if(sumLen % Len) continue; //the original length cann't be Len (优化一)
            Original_Len = Len;
            Original_Num = sumLen / Len;
            if(dfs(0, 0, 0))
            {
                printf("%d\n", Len);
                break;
            }
        }
    }

    return 0;
}