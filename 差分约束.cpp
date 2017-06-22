/*
有n 个人，按从1〜n的顺序排队。对于不同编号的两人A和B有两种关系，分别为喜欢关系和不喜欢关系。输入数据中有X对喜欢关系的人和Y对不喜欢关系的人。对于喜欢关系的两人有一个距离C表示这两个人最多相距C。对于不喜欢关系的两人有一个距离C表示这两人至少相距C。
你的任务是求出第1个人到第n个人的最长距离。
Input
第一行一个数T表示有T组测试数据。
每组数据第一行是N,X,Y  （2<=N<=1000)(1<=X,Y<=10000)
接下来X行每行三个数A,B,C。(1<=A<B<=N )  (1<=C<=1000000)
接下来Y行每行三个数A,B,C。(1<=A<B<=C) (1<=C<=1000000)

Output
一个数。
若不可能存在一个可行的排队方式输出-1
如果1到N的距离太大(即1到N不连通）输出-2。
否则输出1到N的最短距离。

Sample Input
1
4 2 1
1 3 8
2 4 15
2 3 4
 

Sample Output
19

*/
#include<iostream>
using namespace std;
int n,ml,md,st,len,list[1010],d[1010],first[1010],ru[1010];
bool v[1010];
struct node
{  int x,y,next,d;
}edge[21000];
void add(int x,int y,int d)
{   edge[++len].x=x;edge[len].y=y;edge[len].d=d;
    edge[len].next=first[x];first[x]=len;
} 
bool spfa(int st)
{   int head=0,i,x,y;
    for (i=n;i>=1;i--){
         v[i]=false;d[i]=2000000000;ru[i]=0;
         if (first[i]!=-1){
         	 list[++head]=i;
         	 v[i]=true;ru[i]++;
         }
    }d[list[head]]=0;
	bool bo=true;
	while (head!=0)
	{    x=list[head];head--; v[x]=false;;
	     int k=first[x];
	     while (k!=-1)
	     {
	     	  y=edge[k].y;
	     	  if (d[y]>d[x]+edge[k].d)
	     	  {   d[y]=d[x]+edge[k].d;
	     	      if (!v[y])
	     	      {   v[y]=true;
	     	          list[++head]=y;
	     	          ru[y]++;
	     	          if (ru[y]>n+1)return false;
	     	      }     
	     	  }
	     	  k=edge[k].next;	 
	     } 
	}
	return true;
}
int main()
{  int t,i,x,y,c;char s[5];
   scanf("%d",&t);
   while (t-->0){
   scanf("%d%d%d",&n,&ml,&md);
   len=0;memset(first,-1,sizeof(first));
   for (i=1;i<=ml;i++){
  	   scanf("%d%d%d",&x,&y,&c);
  	   add(x,y,c);
   }
   for (i=1;i<=md;i++)
   {    scanf("%d%d%d",&x,&y,&c);
        add(y,x,-c);
   }
   if (spfa(1)){
      if (d[n]>1000000000)printf("-2\n");
	  else printf("%d\n",d[n]);
   }
   else printf("-1\n");
   }
}
