/*
Problem Description
��˵��ңԶ�ĵط���һ���ǳ���ԣ�Ĵ���,��һ��,�峤���������ƶȸĸ���·��䷿�ӡ�
�����һ������,��ϵ�������ס�����Ⱑ�����ﹲ��n�䷿��,�պ���n���ϰ���,���ǵ�ÿ
�Ҷ�Ҫ�з�ס��������ϰ���û����ס�Ļ����������𲻰������أ���ÿ�ұ�����䵽һ��
������ֻ�ܵõ�һ�䷿�ӡ�
��һ����,�峤������Ĵ��쵼ϣ���õ�����Ч��,��������Ļ����Ż���Ǯ.�����ϰ���
���Ƚϸ�ԣ,���Ƕ��ܶ�ÿһ�䷿�������ǵľ��÷�Χ�ڳ�һ���ļ۸�,������3�䷿��,һ��
�ϰ��տ��ԶԵ�һ���10��,�Ե�2���2��,�Ե�3���20��.(��Ȼ�������ǵľ��÷�Χ��).
�������������Ǵ��쵼�������䷿�Ӳ���ʹ�������.(����ʹ��Ǯ����һ�䷿�ӵ���һ
������,Ҫ�����쵼�����).

Input
�������ݰ����������������ÿ�����ݵĵ�һ������n,��ʾ���ӵ�����(Ҳ���ϰ��ռҵ�����)��
��������n��,ÿ��n������ʾ��i�������Ե�j�䷿���ļ۸�(n<=300)��

Output
���ÿ�����������������ֵ��ÿ������ռһ�С�

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
int n; //������Ŀ
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
	memset(ly,0,sizeof(ly)); //��ʼʱ�ұߵĵ������ֵΪ0
	//��ʼʱ��ߵĵ�ı��ֵ����Ϊ�򷿸��������ֵ
	for(int i=0;i<n;++i){
		lx[i] = g[i][0];
		for(int j=1;j<n;++j) lx[i] = lx[i]>g[i][j]? lx[i]:g[i][j];
	}
	//Ϊÿ���˰��ŷ��� 
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
	//ƥ�����,������а�������ƥ��ķ��ӵ�Ǯ
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
