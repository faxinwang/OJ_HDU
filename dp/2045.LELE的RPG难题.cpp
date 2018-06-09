/*
不容易系列之(3)—— LELE的RPG难题
Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)

Problem Description
人称“AC女之杀手”的超级偶像LELE最近忽然玩起了深沉，这可急坏了众多“Cole”（LELE的粉丝,即"可乐"）,
经过多方打探，某资深Cole终于知道了原因，原来，LELE最近研究起了著名的RPG难题:

有排成一行的ｎ个方格，用红(Red)、粉(Pink)、绿(Green)三色涂每个格子，每格涂一色，要求任何相邻
的方格不能同色，且首尾两格也不同色．求全部的满足要求的涂法.

以上就是著名的RPG难题.

如果你是Cole,我想你一定会想尽办法帮助LELE解决这个问题的;如果不是,看在众多漂亮的痛不欲生的Cole
女的面子上,你也不会袖手旁观吧?

Input
输入数据包含多个测试实例,每个测试实例占一行,由一个整数N组成，(0<n<=50)。
 
Output
对于每个测试实例，请输出全部的满足要求的涂法，每个实例的输出占一行。

Sample Input
1
2

Sample Output
3
6

解题思路:
由于最后一个格子不能和第一个格子颜色相同, 对于第i个格子, 可以通过从i-1的合法涂色方案数涂色第三种颜色
而得到,有f(i-1)种;也可以在i-2个格子的合法涂色方案的基础上,将第i-1个格子涂上与第一个格子相同的颜色, 
这时第i个格子就有两种可涂的颜色,有f(i-2)*2种, 综合起来有f(i) = f(i-1) + f(i-2)*2;
*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int maxn = 55;

LL f[maxn]; //f[i]为i个方格时合法的涂色方案数

LL init(int n)
{
   f[1] = 3;
   f[2] = 6;
   f[3] = 6;
   //不同从f[3]开始使用递推公式, 因为递推公式中要求f[i-1]与f[1]颜色相同, 
   //i=3的时候i-1=2,与1相连,而题目要求相连的格子颜色不相同
   for(int i=4; i<=n; ++i) f[i] = f[i-1] + f[i-2]*2;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif
    int N;
    init(50);
    while(~scanf("%d",&N)) printf("%lld\n",f[N]);

    return 0;
}