#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define maxn 110
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
struct tree_node{
    int l,r,lc,rc,c;
    double len;
    int mid(){return (l+r)>>1;}
}t[maxn<<2];
struct node{
    double ydown,yup,x;
    int col;
    void doit(double a,double b,double c,int d){
        ydown=a;yup=b;x=c;col=d;
        return;
    }
}list[maxn<<1];
double ys[maxn<<1],ans;
int n,len,sum;
bool cmp1(double xx,double yy){return xx<yy;}
bool cmp2(const node &n1,const node &n2){return n1.x<n2.x;}
inline void bt(int l,int r){
    int now=++len;
    t[now].l=l;t[now].r=r;t[now].c=0;
    t[now].len=0;
    if(l<r-1){
        int mid=t[now].mid();
        t[now].lc=len+1;bt(l,mid);
        t[now].rc=len+1;bt(mid,r);
    }else t[now].lc=t[now].rc=-1;
}
int find(double x){
    int l=1,r=sum;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ys[mid]==x)return mid;
        if(ys[mid]<x)l=mid+1;
        else r=mid-1;
    }
    return l;
}
inline void updata(int now){
    if(t[now].c)t[now].len=ys[t[now].r]-ys[t[now].l];
    else if(t[now].l+1==t[now].r)t[now].len=0;
    else t[now].len=t[t[now].lc].len+t[t[now].rc].len;
}
inline void ins(int now,int l,int r,int c){
    if(t[now].l==l&&t[now].r==r){
        t[now].c+=c;updata(now);
        return;
    }
    int lc=t[now].lc,rc=t[now].rc,mid=t[now].mid();
    if(r<=mid)ins(lc,l,r,c);
    else if(mid<=l)ins(rc,l,r,c);
    else{ins(lc,l,mid,c);
	     ins(rc,mid,r,c);}
    updata(now);
}
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
    while(scanf("%d",&n),n>0){
        rep(i,1,n){
            double x11,y11,x22,y22;
            scanf("%lf%lf%lf%lf",&x11,&y11,&x22,&y22);
            ys[i*2-1]=y11;ys[i*2]=y22;
            list[i*2-1].doit(y11,y22,x11,1);
            list[i*2].doit(y11,y22,x22,-1);
        }
        sort(ys+1,ys+1+2*n,cmp1);
        ys[sum=1]=ys[1];
        rep(i,2,2*n)
            if(ys[i]!=ys[i-1])ys[++sum]=ys[i];
        sort(list+1,list+1+2*n,cmp2);
        len=0;bt(1,sum);
        ans=0.0;
        rep(i,1,2*n){
            int a=find(list[i].ydown),b=find(list[i].yup);
            ins(1,a,b,list[i].col);
            if(i<2*n)ans+=t[1].len*(list[i+1].x-list[i].x);
        }
       printf("%.2lf\n",ans);
    }
    return 0;
}