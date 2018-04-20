/*
Problem Description
Sakura has a very magical tool to paint walls. One day, kAc asked Sakura to paint a wall that looks 
like an M×N matrix. The wall has M×N squares in all. In the whole problem we denotes (x,y) to be the 
square at the x-th row, y-th column. Once Sakura has determined two squares (x1,y1) and (x2,y2), she 
can use the magical tool to paint all the squares in the sub-matrix which has the given two squares 
as corners.

However, Sakura is a very naughty girl, so she just randomly uses the tool for K times. More 
specifically, each time for Sakura to use that tool, she just randomly picks two squares from 
all the M×N squares, with equal probability. Now, kAc wants to know the expected number of 
squares that will be painted eventually.
 

Input
The first line contains an integer T(T≤100), denoting the number of test cases.

For each test case, there is only one line, with three integers M,N and K.
It is guaranteed that 1≤M,N≤500, 1≤K≤20.
 

Output
For each test case, output ''Case #t:'' to represent the t-th case, and then output the expected 
number of squares that will be painted. Round to integers.
 

Sample Input
2
3 3 1
4 4 2
 

Sample Output
Case #1: 4
Case #2: 8

Hint
The precise answer in the first test case is about 3.56790123.

题目大意:
在一个M*N的矩阵中随机选择一个任意大小的子矩阵(i*j, 1<=i<=M, 1<=j<=N)并将该子矩阵涂色,求最后被涂色
的格子的个数的数学期望.

解题思路:
染色格子数的期望值 = 每个格子被染色的概率和
E(x) = Sum( p(i,j) ) (i=1...M, j=1...N)

一次染色中第i行被染色的概率:
不被染色即选择的子矩阵要么在第i行上面要么在第i行下面, 在上面时子矩阵的上下边界出现在前i-1行, 
在下面是子矩阵的上下边界出现在后M-i行, 所以一次染色不被涂中的概率为 (i-1)*(i-1)/(m*m) + 
(m-i)*(m-i)/(m*m), 所以一次涂色被涂中的概率为:
p(i) = 1 - (i-1)(i-1)/(m*m) - (m-i)(m-i)/(m*m)

同理,一次涂色中第j列被涂色的概率:
p(j) = 1 - (j-1)(j-1)/(n*n) - (n-j)(n-j)/(n*n)

所以一次涂色中格子(i,j)被涂色的概率为:
p1(i,j) = p(i)*p(j)

所以k次涂色中格子(i,j)被涂色的概率为:
pk(i,j) = 1 - ( 1 - p1(i,j) )^k

为什么不直接求k次涂色后格子(i,j)被染色的概率呢? 因为麻烦.
设一次染色某个格子被覆盖的概率为p1,则k次涂色后格子(i,j)被覆盖的概率为:
pk(i,j) = C(1, k)p1(1-p1)^(k-1) + C(2,k)p1^2(1-p1)^(k-2) + ... + C(k,k)p1^k.

*/


#include<iostream>
#include<cstdio>
using namespace std;

int T, M, N, k; //M rows, N cols, k times paints    


//一次染色中第i行或第i列被覆盖的概率
double p(int i, int n)
{
    double t1 = i-1, t2=n-i;
    return 1.0 - (t1*t1 + t2*t2)/(n*n);
}

// //格子(i,j)在一次染色中被覆盖的概率
// double p1(int i,int j)
// {
//     return p(i,M) * p(j,N);
// }

//格子(i,j)在k次染色中被覆盖的概率
double pk(int i,int j, int k)
{
    // double notPaint = 1.0 - p1(i, j), p=1;
    double notPaint = 1.0 -  p(i, M) * p(j, N), p=1;
    for(int t=0; t<k; ++t)  p *= notPaint;
    return 1 - p;
}

double Ex(int row, int col, int k)
{
    double ex = 0;
    for(int r=1; r<=row; ++r)
    {
        for(int c=1; c<=col; ++c)
        {
            ex += pk(r, c, k);
        }
    }
    return ex;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    scanf("%d",&T);
    for(int kiss=1; kiss<=T; ++kiss)
    {
        scanf("%d%d%d",&M, &N, &k);
        printf("Case #%d: %.0lf\n", kiss, Ex(M, N, k));
    }

    return 0;
}