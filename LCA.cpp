#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node{int y,d,next;}edge[20010];
struct nnode{int dis,par[14],dep;}t[10010];
int n,m,len,first[10010],maxx=14;
inline void ins(int x,int y,int d)
{  edge[++len].y=y;edge[len].d=d;
   edge[len].next=first[x];first[x]=len;
}
inline void build(int x,int fa)
{   int i,k;
    t[x].par[0]=fa;t[x].dep=t[fa].dep+1;
    for (i=1;t[x].dep-(1<<i)>=1;i++)
	   t[x].par[i]=t[t[x].par[i-1]].par[i-1];
    for (k=first[x];k!=-1;k=edge[k].next)
	   if (edge[k].y!=fa){
          t[edge[k].y].dis=t[x].dis+edge[k].d;
	      build(edge[k].y,x);
	   }
}
inline int LCA(int x,int y)
{ int i;
  if (t[x].dep<t[y].dep){int tt;tt=x;x=y;y=tt;}
  for(i=maxx;i>=0;i--)
     if (t[x].dep-t[y].dep>=(1<<i))
        x=t[x].par[i];
  if (x==y)return x;
  for (i=maxx;i>=0;i--)
     if (t[x].dep>(1<<i)&&t[x].par[i]!=t[y].par[i])
     {   x=t[x].par[i];y=t[y].par[i];
     }
  return t[x].par[0];
}
inline int find(int x,int y,int kth)
{  int fa=LCA(x,y),i;kth--;
   for (i=maxx;i>=0;i--)
      if (t[x].dep-t[fa].dep>=(1<<i)&&kth>=(1<<i))
      {   kth=kth-(1<<i);
          x=t[x].par[i];
      } 
   if (kth==0)return x;
   int left=t[y].dep-t[fa].dep;
   for (i=maxx;i>=0;i--)
      if (left-(1<<i)>=kth){
      	  y=t[y].par[i];
      	  left=left-(1<<i);
      }
   return y;
}
int main()
{   int T,x,y,d,i;char s[10];
	scanf("%d",&T);
	while (T-->0){
		scanf("%d",&n);len=0;
		memset(first,-1,(n+1)*sizeof(int));
		for (i=1;i<n;i++){
            scanf("%d%d%d",&x,&y,&d);
            ins(x,y,d);ins(y,x,d);
 		}t[1].dis=0;build(1,0);
 		while (scanf("%s",s),s[1]!='O')
 		{   if (s[0]=='D'){
 			    scanf("%d%d",&x,&y);
 			    printf("%d\n",t[x].dis+t[y].dis-2*t[LCA(x,y)].dis);
 		    }
 		    else {
 		    	scanf("%d%d%d",&x,&y,&d);
 		        printf("%d\n",find(x,y,d));
 		    }
 		}
	}
}