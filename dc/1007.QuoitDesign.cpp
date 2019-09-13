/*
Quoit Design
Time Limit: 10000/5000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)

Problem Description
Have you ever played quoit in a playground? Quoit is a game in which flat rings 
are pitched at some toys, with all the toys encircled awarded.
In the field of Cyberground, the position of each toy is fixed, and the ring is 
carefully designed so it can only encircle one toy at a time. On the other hand, 
to make the game look more attractive, the ring is designed to have the largest 
radius. Given a configuration of the field, you are supposed to find the radius 
of such a ring.

Assume that all the toys are points on a plane. A point is encircled by the ring 
if the distance between the point and the center of the ring is strictly less than 
the radius of the ring. If two toys are placed at the same point, the radius of 
the ring is considered to be 0.

Input
The input consists of several test cases. For each case, the first line contains 
an integer N (2 <= N <= 100,000), the total number of toys in the field. Then N 
lines follow, each contains a pair of (x, y) which are the coordinates of a toy. 
The input is terminated by N = 0.

Output
For each test case, print in one line the radius of the ring required by the 
Cyberground manager, accurate up to 2 decimal places. 

Sample Input
2
0 0
1 1
2
1 1
1 1
3
-1.5 0
0 0
0 1.5
0

Sample Output
0.71
0.00
0.75

解法:
设点集为S

对于一维情况,伪代码入戏:
预处理:
double closestPair(S){
    n = |S|
    if(n < 2) return INF;
    m = S中各点坐标的中位数
    构造左子集  S1 = {x属于S| x<=m }
    构造右子集  S2 = {x属于S| x>m}
    double dl = closestPair(S1)
    double dr = closestPair(S2)
    p = max(S1)
    q = min(S2)
    return min(dl,dr, q - p);
}

对于二维情况,伪代码如下:
double closestPair(S){
    n = |S|
    if(n < 2) return INF;
    if(2 <= n <= 3) return 直接计算这两三个点之间的最短距离;
    m  = S中各点之间的横坐标的中位数,在代码中可以取数组中间的那个点的横坐标;
    构造左子集 S1 = {p属于S|p.x <= m}
    构造右子集 S1 = {p属于S|p.x > m}
    double dl = closestPair(S1)
    double dr = closestPair(S2)
    double dm = min(dl,dr)
    P1 = 横坐标属于区间[m- md, m]中的点, 按纵坐标排序
    P2 = 横坐标属于区间[m, m+md]中的点, 按纵坐标排序
    对于P1中的任意点p, P2中可能与p形成最短距离的候选点只可能出现在[m : m+md, p.y-md : p.y+md]的方形区域内,且最多只有6个
    因此,对于p1中的每个点, 只需要计算p2中与其纵坐标距离最近的6个点之间的距离,设这六个距离的最小值为d, 令dm = min(dm, d)
    return md;
}
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 1E5+5;
const int INF = 1E8;
#define LEFT -1
#define RIGHT 1

struct Point{
    int id;
    double x,y;
};

vector<Point> X(MAXN); //保存按x坐标排序后的点
vector<Point> Y(MAXN); //保存按y坐标排序后的点
int id2idx[MAXN];

bool cmpx(const Point& a, const Point& b){ return a.x < b.x; }
bool cmpy(const Point& a, const Point& b){ return a.y < b.y; }

double dist(Point& a, Point& b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double closestPair(int L, int R){ //前开后闭
    int n = R - L;
    if(n < 2) return INF;
    if(n == 2) return dist(X[L], X[L+1]);
    if(n == 3){
        Point &a = X[L], &b = X[L+1], &c = X[L+2];
        double d1 = dist(a,b);
        double d2 = dist(a,c);
        double d3 = dist(b,c);
        return min(d1, min(d2,d3));
    }
    
    int mid = (L+R) >> 1;
    double dl = closestPair(L, mid);
    double dr = closestPair(mid, R);
    double md = min(dl, dr);

    double L1 = X[mid].x - md;
    double L2 = X[mid].x + md;

    vector<Point> v;
    for(int i=L; i<mid; ++i) if(X[i].x >= L1){ //注意<=, 要包括边界线上的点
        Point p = Y[ id2idx[X[i].id] ];
        p.id = LEFT;
        v.push_back(p);
    }
    for(int i=mid; i<R; ++i) if(X[i].x <= L2){  //注意>=, 要包括边界线上的点
        Point p = Y[ id2idx[X[i].id] ];
        p.id = RIGHT;
        v.push_back(p);
    }

    double d = INF;
    for(int i=0, m=v.size(); i<m; ++i){
        for(int k=1; k<=7 && i+k<m; ++k)
            if(v[i].id != v[i+k].id) d = min(d, dist(v[i],v[i+k]));
    }
    return min(md, d);
}

int main(){
    #ifdef WFX
    freopen("in.txt","r",stdin);
    #endif

    int n;
    while(scanf("%d",&n) && n){
        for(int i=0; i<n; ++i){
            scanf("%lf%lf", &X[i].x, &X[i].y);
            X[i].id = i;
            Y[i] = X[i];
        }
        sort(X.begin(), X.begin()+n, cmpx);
        sort(Y.begin(), Y.begin()+n, cmpy);
        for(int i=0; i<n; ++i) id2idx[ Y[i].id ] = i;

        printf("%.2lf\n", closestPair(0, n)/2 );
    }

    return 0;
}
