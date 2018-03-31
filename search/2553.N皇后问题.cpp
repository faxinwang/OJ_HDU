/*
Problem Description
在N*N的方格棋盘放置了N个皇后，使得它们不相互攻击（即任意2个皇后不允许处在同一排，同一列，
也不允许处在与棋盘边框成45角的斜线上。你的任务是，对于给定的N，求出有多少种合法的放置方法。

Input
共有若干行，每行一个正整数N≤10，表示棋盘和皇后的数量；如果N=0，表示结束。
 
Output
共有若干行，每行一个正整数，表示对应输入行的皇后的不同放置数量。
 
Sample Input
1
8
5
0

Sample Output
1
92
10

解题思路：
从第一行到第N行依次枚举当前中可以放置皇后的位置。
用三个变量L, col, R中的二进制位来分别表示当前行在左斜线(从右上角到左下角)，列，右斜线(从左上角到右下角)
中会被攻击的位置，然后通过位运算即可快速求出当前行中可以放置皇后的位置，然后依次尝试在当前行的每一个可以放置
皇后的位置上放置一个皇后，然后通过该位置计算出下一行中L, col, R的值，
*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned int Uint;
Uint N, ans, all;

void search(Uint L, Uint col, Uint R)
{
    //如果每一列都放了皇后，则得到了一个可行解。
    if(col == all) ++ans;
    else
    {
        Uint pos = all & ~(L | col | R); //得到当前行中可以放置皇后的位置
        while(pos)
        {
            Uint bit = pos & -pos;
            pos -= bit; //在当前行的bit位置放置皇后
            search((L|bit)<<1, col|bit, (R|bit)>>1);
        }
    }
}

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif 
    while(scanf("%d",&N) && N)
    {
        all = (1<<N) - 1; //设置all的低N位为全1
        ans = 0;
        search(0,0,0);
        cout<<ans<<endl;
    }

    return 0;
}