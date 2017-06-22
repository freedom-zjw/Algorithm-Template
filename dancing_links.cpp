/*
����һ��n*m��01����Ҫ��ѡ��һЩ�У�ʹ��ÿ�����ҽ���һ��1�����Ƿ���ܡ�
n<=16��m<=300���������ݣ�T<=500��
 */
#include<cstdio>
#include<iostream>
using namespace std;
#define N 20
#define M 310
#define rep(i,u,v) for (int i=(u);i<=(v);i++) 
struct node
{  int l,r,u,d;
}p[N*M];//˫������ 
//��ͷ���Ϊ1��m �� ԭ����ÿ����ı��Ϊ i*m+j 
int data[N][M],lev[M];//dataΪԭ����lev[i]��i�� �ж��ٸ�1
int n,m,s;//s Ϊ���Ͻ�������� n*m+m+1 
int tot,sta[N*M];//sta �Ǽ�¼��ɾ���ڵ��ջ��tot��ջ���ڵ�
void input()
{    rep(i,1,n)
        rep(j,1,m)
        	scanf("%d",&data[i][j]);
     s=n*m+m+1;tot=0;
}
void remove(int t)
{   sta[++tot]=t;
    if (t>m)lev[(t-1)%m+1]--;
    p[p[t].l].r=p[t].r;p[p[t].r].l=p[t].l;
    p[p[t].u].d=p[t].d;p[p[t].d].u=p[t].u;
}
void rebuild()
{   int t=sta[tot--];
    if (t>m)lev[(t-1)%m+1]++;
    p[p[t].l].r=t;p[p[t].r].l=t;
    p[p[t].u].d=t;p[p[t].d].u=t;
}
void delcol(int t)
{   for (int i=p[t].u;i;i=p[t].u)
    {    if (i<=m){remove(i);break;}
         int l=i;while (p[l].l)l=p[l].l;
         for (int j=l;j;j=p[j].r)remove(j);
    }
    for (int i=p[t].d;i;i=p[t].d)
    {    int l=i;while (p[l].l)l=p[l].l;
         for (int j=l;j;j=p[j].r)remove(j);
    }
}
bool search()
{   if (!p[s].r)return true;
    int c=0;
    for (int i=p[s].r;i;i=p[i].r)
        if (!c||lev[i]<lev[c])c=i;
    if (!lev[c])return false;
    int cnt=tot;
    for (int i=p[c].d;i;i=p[i].d)
    {    int l=i;while (p[l].l)l=p[l].l;
         for (int j=l;j;j=p[j].r)delcol(j);
         for (int j=l;j;j=p[j].r)remove(j);
         if (search())return true;
         while (tot>cnt)rebuild();
    }
    return false;
}
void solve()
{    memset(p,0,sizeof(p));
     p[s].r=1;p[1].l=s;
     rep(i,0,n)
        rep(j,1,m-1)
        {    p[i*m+j].r=i*m+j+1;
             p[i*m+j+1].l=i*m+j;
        }
     rep(i,0,n-1)
        rep(j,1,m)
        {   p[i*m+j].d=i*m+j+m;
            p[i*m+m+j].u=i*m+j;
        }
     rep(i,1,m)lev[i]=n;
     rep(i,1,n)
         rep(j,1,m)
             if (!data[i][j])remove(i*m+j);
	 if (search())printf("Yes, I found it\n");
	 else printf("It is impossible\n");
}
int main()
{    while (scanf("%d%d",&n,&m)==2)
     {    input();
          solve();
     }
} 