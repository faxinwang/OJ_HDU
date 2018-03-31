/*
Problem Description
传说在遥远的地方有一个非常富裕的村落,有一天,村长决定进行制度改革：重新分配房子。
这可是一件大事,关系到人民的住房问题啊。村里共有n间房间,刚好有n家老百姓,考虑到每
家都要有房住（如果有老百姓没房子住的话，容易引起不安定因素），每家必须分配到一间
房子且只能得到一间房子。
另一方面,村长和另外的村领导希望得到最大的效益,这样村里的机构才会有钱.由于老百姓
都比较富裕,他们都能对每一间房子在他们的经济范围内出一定的价格,比如有3间房子,一家
老百姓可以对第一间出10万,对第2间出2万,对第3间出20万.(当然是在他们的经济范围内).
现在这个问题就是村领导怎样分配房子才能使收入最大.(村民即使有钱购买一间房子但不一
定能买到,要看村领导分配的).

Input
输入数据包含多组测试用例，每组数据的第一行输入n,表示房子的数量(也是老百姓家的数量)，
接下来有n行,每行n个数表示第i个村名对第j间房出的价格(n<=300)。

Output
请对每组数据输出最大的收入值，每组的输出占一行。

Sample Input
2
100 10
15 23
 

Sample Output
123

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 305
using namespace std;
const int INF = 1<<30;

bool visX[maxn],visY[maxn];
int lx[maxn],ly[maxn];
int slack[maxn];
int match[maxn];
int g[maxn][maxn];
int n; //百姓数目
int d = INF;

bool dfs(int x){
	visX[x] = true;
	for(int y=0;y<n;++y){
		if(visY[y]) continue;
		int gap = lx[x] + ly[y] - g[x][y];
		if(gap == 0){
			visY[y] = true;
			if(match[y]==-1 || dfs(match[y])){
				match[y] = x;
				return true;
			}
		}else slack[y] = slack[y]<gap? slack[y]:gap;
	}
	return false;
}

int KM(){
	memset(match,-1,sizeof(match));
	memset(ly,0,sizeof(ly)); //初始时右边的点的期望值为0
	//初始时左边的点的标号值是他为买房付出的最大值
	for(int i=0;i<n;++i){
		lx[i] = g[i][0];
		for(int j=1;j<n;++j) lx[i] = lx[i]>g[i][j]? lx[i]:g[i][j];
	}
	//为每个人安排房子 
	for(int x=0;x<n;++x){
		fill(slack,slack+n,INF);
		while(1){
			memset(visX,0,sizeof(visX));
			memset(visY,0,sizeof(visY));
			if(dfs(x)) break;
			for(int j=0;j<n;++j) if(!visY[j]) d = d<slack[j]?d:slack[j];
			for(int k=0;k<n;++k){
				if(visX[k]) lx[k] -= d;
				if(visY[k]) ly[k] += d;
				else slack[k] -= d;
			} 
		}
	}
	//匹配完成,求出所有百姓与其匹配的房子的钱
	int  sum=0;
	for(int y=0;y<n;++y) sum += g[match[y]][y];
	return sum;
}

int main() {
#ifdef WFX
freopen("HDU2255 in.txt","r",stdin);
#endif 
	while(scanf("%d",&n)!=-1){
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				scanf("%d",&g[i][j]);
			}
		}
		printf("%d\n",KM());
	}
	
	
	return 0;
}
