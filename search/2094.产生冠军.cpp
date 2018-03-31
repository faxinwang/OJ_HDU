/*
Problem Description
有一群人，打乒乓球比赛，两两捉对撕杀，每两个人之间最多打一场比赛。
球赛的规则如下：
如果A打败了B，B又打败了C，而A与C之间没有进行过比赛，那么就认定，A一定能打败C。
如果A打败了B，B又打败了C，而且，C又打败了A，那么A、B、C三者都不可能成为冠军。
根据这个规则，无需循环较量，或许就能确定冠军。你的任务就是面对一群比赛选手，在经过了若干场撕杀之后，
确定是否已经实际上产生了冠军。

Input
输入含有一些选手群，每群选手都以一个整数n(n<1000)开头，后跟n对选手的比赛结果，比赛结果以一对选手名字
（中间隔一空格）表示，前者战胜后者。如果n为0，则表示输入结束。

Output
对于每个选手群，若你判断出产生了冠军，则在一行中输出“Yes”，否则在一行中输出“No”。

Sample Input
3
Alice Bob
Smith John
Alice Smith
5
a c
c d
d e
b e
a d
0

Sample Output
Yes
No

解题思路：
参考：https://www.cnblogs.com/blumia/p/hdu2094.html

和别人一样，想过是并查集。
还想过建立有向图，然后用dfs去掉所有的环和被环上的人打败的人，但时感觉稍微有点麻烦。

然后就看到了博主的思路，感觉很简洁。

就是把所有胜利过的人放到winers集合，吧所有失败过的人放到losers集合，然后对于winers
集合里面的每一个人，看他是否也在losers集合里面(即看他是否失败过)， 如果在，那他就不可能是
冠军，如果不在，就将计数器winCnt加一，最后如果winCnt==1就说明可以确定冠军，否则不可以。
*/

#include<iostream>
#include<cstdio>
#include<set>
#include<string>
using namespace std;

int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    string win,lose;
    int n;
    while(scanf("%d",&n) && n)
    {
        set<string> winers, losers;
        for(int i=0;i<n;++i)
        {
            cin>>win>>lose;
            winers.insert(win);
            losers.insert(lose);
        }
        int winCnt = 0;
        set<string>::iterator it = winers.begin();
        for(; it !=  winers.end(); ++it)
        {
            if(losers.find(*it) == losers.end()) ++winCnt;
        }
        printf("%s\n", winCnt==1? "Yes" : "No");
    }

    return 0;
}