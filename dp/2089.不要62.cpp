/*
Problem Description
杭州人称那些傻乎乎粘嗒嗒的人为62（音：laoer）。
杭州交通管理局经常会扩充一些的士车牌照，新近出来一个好消息，以后上牌照，不再含有不吉利的数字了，
这样一来，就可以消除个别的士司机和乘客的心理障碍，更安全地服务大众。
不吉利的数字为所有含有4或62的号码。例如：
62315 73418 88914
都属于不吉利号码。但是，61152虽然含有6和2，但不是62连号，所以不属于不吉利数字之列。
你的任务是，对于每次给出的一个牌照区间号，推断出交管局今次又要实际上给多少辆新的士车上牌照了。
 

Input
输入的都是整数对n、m（0<n≤m<1000000），如果遇到都是0的整数对，则输入结束。

Output
对于每个整数对，输出一个不含有不吉利数字的统计个数，该数值占一行位置。
 
Sample Input
1 100
0 0
 
Sample Output
80

解题思路：
方法一：
dp[len][if6]表示长度为len位， 前一位是否为6时可行的数字个数
方法二：
dp[pos][prev]表示当前处在第pos位，前一位为prev时可行的数字个数
*/ 

#include<iostream> 
#include<cstdio>
#include<cstring>
using namespace std;

int bits[20];
int dp[20][10];


//dp[len][if6]长度为len位，前一位是否为6时可行的数字个数 
//int dfs(int len,int if6, bool limit){
//	if(len==0) return 1;
//	if(!limit && dp[len][if6] != -1) return dp[len][if6];
//	int up = limit? bits[len] : 9; //枚举当前位的数字 
//	int cnt = 0;
//	for(int i=0; i<=up; ++i){
//		if( i==4 || (if6 && i==2) ) continue;
//		cnt += dfs(len-1, i==6, limit&&i==up);
//	}
//	return limit? cnt : dp[len][if6] = cnt;
//}
//
//int solve(int n){
//	int k=0;
//	while(n){
//		bits[++k] = n%10;
//		n /= 10;
//	}
//	return dfs(k, 0, true );
//}


//dp[pos][prev]表示当前处在第pos位(个位数的位置为0)，前一位为prev时可行的数字个数。 
int dfs(int pos, int prev, bool limit)
{
	
	if(pos == 0) return 1; //或者pos==-1 
	if(!limit && dp[pos][prev] != -1) return dp[pos][prev]; //2 
	int up = limit? bits[pos-1] : 9; //枚举下一位数字 
	int cnt = 0;
	for(int d=0; d<=up; ++d)
	{
		if(d == 4 || (prev==6 && d==2)) continue; //当前数字是4或者前一位是6且当前位是2，则直接跳过 
		cnt += dfs(pos-1, d, limit && d==up);  
	}
	return limit? cnt : dp[pos][prev] = cnt; 
}


int solve(int n)
{
	int len = 0;
	while(n) 
	{
		bits[len++] = n % 10;
		n /= 10; 
	}
	return dfs(len, 0, true);
}


int main(){
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
	int a,b;
	memset(dp,-1,sizeof(dp)); 
	while(scanf("%d%d",&a,&b) && a && b){
		//因为该dp状态只与数字特征有关，与输入数据无关，所以已经计算出的状态可以复用 
		printf("%d\n",solve(b) - solve(a-1));
	}
	
	return 0;
}	
