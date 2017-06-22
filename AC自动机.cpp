/*
给一个母串，和n个子串问最少修改几个字母能使母串不含任何一个子串，如果不能输出-1
代码：
 */
#include<iostream>
#define rep(a,b,c) for (int a=b;a<=c;a++)
#define INF 1000000000
using namespace std;
char s[201],ss[2010];
struct node{
	int fail,times,c[5];
	void init()
	{  memset(c,0,sizeof(c));
	   times=0;fail=0;
	}
}t[2010];
int n,list[2010],dp[2010][2010],tot;
int get(char ch)
{  if (ch=='A')return 1;
   else if (ch=='C')return 2;
   else if (ch=='G')return 3;
   else return 4;
}
void ins(char *s)
{  int p=0,idx;
   while (*s)
   {   idx=get(*s);
       if (!t[p].c[idx])
       {   t[p].c[idx]=++tot;
           t[tot].init();
       }
       p=t[p].c[idx];
       s++;
   }
   t[p].times=1;
}
void build_ac_auto()
{  int p=0,head,tail=1,son,x;list[1]=0;
   rep(head,1,tail)
   {    x=list[head];
        rep(i,1,4)
        {   p=t[x].fail;son=t[x].c[i];
		    if (t[x].c[i])
            {   if (x==0)t[son].fail=0;
                else {
				   t[son].fail=t[p].c[i];
                   t[son].times|=t[t[son].fail].times;
				}
                list[++tail]=son;
            }
            else{
          	    if (x==0)t[x].c[i]=0;
				else t[x].c[i]=t[p].c[i]; 
            }
        }
   }
}
int main()
{   int T=0,len,son,ans; 
    while (scanf("%d",&n),n>0)
    {   
        tot=0;t[0].init();
        rep(i,1,n)
        {  scanf("%s",s);
           ins(s);
        }
        build_ac_auto();
        scanf("%s",ss);
        len=strlen(ss);
        rep(i,0,len)
           rep(j,0,tot)
              dp[i][j]=INF;
        dp[0][0]=0;
        rep(i,0,len-1)
        {    rep(j,0,tot)
             {   if (dp[i][j]!=INF&&!t[j].times)
                 {    rep(k,1,4)
                      {   son=t[j].c[k];
                          if (!t[son].times){
                             if (k!=get(ss[i]))
                               dp[i+1][son]=min(dp[i+1][son],dp[i][j]+1);
                             else dp[i+1][son]=min(dp[i+1][son],dp[i][j]);
                          }
                      }
                 }
             }
        }ans=INF;
        rep(i,0,tot)
          ans=min(ans,dp[len][i]);
        if (ans==INF)ans=-1;
        printf("Case %d: %d\n",++T,ans);
    }
}