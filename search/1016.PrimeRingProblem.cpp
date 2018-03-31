/*
Problem Description
A ring is compose of n circles as shown in diagram. Put natural number 1, 2, ..., n into each 
circle separately, and the sum of numbers in two adjacent circles should be a prime.

Note: the number of first circle should always be 1.

Input
n (0 < n < 20).

Output
The output format is shown as sample below. Each row represents a series of circle numbers in 
the ring beginning from 1 clockwisely and anticlockwisely. The order of numbers must satisfy 
the above requirements. Print solutions in lexicographical order.

You are to write a program that completes above process.
Print a blank line after each case.


Sample Input
6
8
 

Sample Output
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2

解题思路：
因为n最大为20，所以相邻两个结点的和最大不超过40，所以只需要把100或者50以内的素数表打出来就可以了。
然后就是简单的DFS搜索，从编号1开始，往顺时针方向枚举下一个没有使用过的数字，并且该数字与当前数字
的和为素数，即可在下一个位置放置该数字，当枚举完最后一个数字后，判断最后一个数字与第一个数字的和是否也
是素数，如果是，就说明找到了一个可行的解。

最后对所有可行的解按照字符表顺序排序即可。

*/


#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
const int maxn = 100;

bool p[maxn], vis[30];
vector<vector<int> > vv;
vector<int> v;
int N;

void init(int n)
{
    for(int i=2; i*i<=n; ++i)
        if(!p[i])
            for(int j=i*i; j<=n; j+=i)
                p[j] = 1;
}

//参数k为向量v中最后一个元素的下标，k+1即为元素个数
void dfs(int k)
{
    if(k + 1 == N)
    {
        if( p[v[0] + v[k]] == 0 ) vv.push_back(v);
        return;
    }
    for(int i=2; i<=N; ++i) if(!vis[i])
    {
        if( p[ v[k] + i ] == 0 )
        {
            vis[i] = 1;
            v.push_back(i);
            dfs(k+1);
            v.pop_back();
            vis[i] = 0;
        }
    }
}


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int Case=0;
    init(maxn);
    while(~scanf("%d",&N))
    {
        memset(vis,0,sizeof(vis));
        vis[1] = 1;
        vv.clear(); //清空容器
        v.clear(); //清空容器
        v.push_back(1); //题目要求总是以1号结点开始
        dfs(0);

        sort(vv.begin(), vv.end());

        printf("Case %d:\n", ++Case);
        for(int i=0; i<vv.size(); ++i){
            // copy(vv[i].begin(), vv[i].end(), ostream_iterator<int>(cout, " ")); //末尾不能有空格
            vector<int> & v = vv[i];
            printf("%d", v[0]);
            for(int i=1,n=v.size(); i<n; ++i) printf(" %d",v[i]);
            cout<<endl;
        }
        cout<<endl;
    }

    return 0;
}