/*
//bzoj1419
https://www.lydsy.com/JudgeOnline/problem.php?id=1419

Description
桌面上有R张红牌和B张黑牌，随机打乱顺序后放在桌面上，开始一张一张地翻牌，翻到红牌得到1美元，黑牌则付
出1美元。可以随时停止翻牌，在最优策略下平均能得到多少钱。
Input
一行输入两个数R,B,其值在0到5000之间

Output
在最优策略下平均能得到多少钱。

Sample Input
5 1

Sample Output
4.166666

HINT
输出答案时,小数点后第六位后的全部去掉,不要四舍五入.

解题思路:
参考:https://blog.csdn.net/MintGreenTZ/article/details/74549584

最优取牌策略:
当红牌数R>黑牌数B时才取牌,否则不继续取牌

当红牌数为R,黑牌数为B时, 在最优策略下, 获得金币的数学期望为:
F(R, B) = ( F(R-1, B) + 1)*p(获取红牌的概率) + (F(R, B-1) - 1)*p(获取黑牌的概率)
p(获取红牌的概率) = R / (R + B)
p(获取黑牌的概率) = B / (R + B)
递归基:
当 B=0 时, F(R, 0 ) = R;
当 R<=B 时, 不继续取牌, 所以 F(R ,B) = 0;

*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std; 
const int maxn = 5005;

//备忘录数组, f[i][j]表示有i张红牌和j张黑牌时在最优取牌策略下获得金币的数学期望
// double f[maxn][maxn];

// double F(int R, int B)
// {
//     if( f[R][B] > 0) return f[R][B];
//     if(B == 0) return R; //如果黑牌的个数为0, 则获得金币的期望为红牌的个数R
//     if(R <= B) return 0; //如果红牌的个数小于等于黑牌的个数, 则获得金币的期望 <= 0, 此时应该选择不继续去牌
//     f[R][B] = ( F(R-1, B) + 1 ) * ((double) R / (R+B)) //取得红牌
//                    + ( F(R, B-1) - 1 ) * ((double) B / (R+B)); //取得黑牌
//     // printf("F(%d, %d)=%lf\n", R,B, f[R][B]);
//     return f[R][B];
// }


//使用滚动数组优化内存
double f[2][maxn];

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    int R, B;
    int last=0, now=1;
    // memset(f,-1,sizeof(f));
    scanf("%d%d" ,&R, &B);
    for(int i=1; i<=R; ++i, last^=1, now^=1)
    {
        memset(f[now], 0, sizeof(f[now]));
        f[now][0] = i;
        for(int j=1; j<=B; ++j)
        {
            double Ex_ij = (f[last][j] + 1) * i + (f[now][j-1] - 1) * j;
            Ex_ij /= (i + j);
            f[now][j] = max(f[now][j], Ex_ij);
        }
    }
    // printf("%lf\n", f[last][B]); //4.166667
    printf("%lf\n", int( f[last][B] * 1e6 ) / 1e6); //不进行四舍入五

    return 0;
}