/*
【题目描述】
平面上给定n个点及出现的概率，任意3点不共线。求出现的点构成的凸包的面积的期望值是多少？

【数据范围】
n<=100.

样例输入:
3
0 0 0.5
0 5 0.5
5 0 0.5

样例输出:
1.562500

样例输入:
16
1 4 0.3
1 2 0.2
2 3 0.5
3 4 0.8
5 2 0.6
5 1 0.3
6 7 0.8
7 8 0.9
8 9 1.0
7 9 0.6
2 9 0.9
10 13 0.2
1 9 0.3
10 6 0.3
7 16 0.3
8 3 0.3

样例输出:
58.465873


解题思路:
凸多边形的面积等于多边形外一点O与多边形每条边组成的三角形的有向面积之和,
有向面积 s(A,B) = 1/2 * (OA X OB)

AB作为凸包的边对面积期望的贡献：
f(A,B)= s(A,B) * P(A) * P(B) * P(AB右边的点不出现)

E(S) = sum( f(i,j) ) (i=1...n, j=1...n)
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 105;

struct Point
{
    double x,y;
    Point(){}
    Point(double x, double y):x(x),y(y){}
};

int n; //顶点个数
double p[maxn]; //p[i]为第i个点出现的概率
Point pt[maxn];

//返回向量i和j的叉乘(面积的两倍)
double cross(Point& i, Point& j)
{
    return i.x * j.y - i.y * j.x;
}

/*
边(i,j)作为凸包的边出现的条件是边(i,j)顺时针外侧的顶点都不出现.
如何判断某一个顶点是否在边(i,j)顺时针的外侧:
如果点k出现在边(i,j)顺时针的外侧, 则向量ij与ik的叉乘值大于0,否则小于等于0(等于0时两向量重合)
*/
double asBorder(int i,int j)
{
    Point &a=pt[i], &b=pt[j];
    Point ab(b.x - a.x , b.y - a.y);
    double notShow = 1; //边(i,j)顺时针外侧的点不出现的概率
    for(int k=0; k<n; ++k)
    {
        if(k==i || k==j) continue;
        Point ak(pt[k].x - a.x, pt[k].y - a.y);
        //如果第k个点出现在边(i,j)顺时针的外侧, 就乘上它不出现的概率
        if( cross(ab, ak) > 0) notShow *= 1- p[k];
    }
    return notShow;
}

int main()
{
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    scanf("%d",&n);
    for(int i=0; i<n; ++i) scanf("%lf%lf%lf", &pt[i].x, &pt[i].y, &p[i]);
    
    double Ex = 0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            if(i != j) Ex += cross(pt[i], pt[j]) * p[i] * p[j] * asBorder(i,j);
        }
    }

    Ex /= 2; //叉乘的值为面积的两倍,所以除以2
    if(Ex < 0) Ex = -Ex;
    printf("%.6lf\n", Ex);

    return 0;
}