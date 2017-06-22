#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define maxw 16
#define lowbit(x) ((x)&(-x))
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
#define dto(i,u,v) for (int i=(u);i>=(v);i--)
#define N 50010
struct node{int x,idx,type;}a[N],b[N+10010];
struct nn{int l,r,x;}Q[10010];
struct tree{int son[2],num,sum;}t[N*2*17];
int n,m,tot,cnt;
int ys[60010],root[N],rot[N],Left[N],Right[N];
char s[10010][3];
bool cmp(node n1,node n2){return n1.x<n2.x;}
void init(){
	tot=0;
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%d",&a[i].x);
		a[i].idx=i;a[i].type=1;
		b[++tot]=a[i];
	}
	rep(i,1,m){
			scanf("%s",s[i]);
			if (s[i][0]=='Q')scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].x);
			else {
				scanf("%d%d",&Q[i].l,&Q[i].x);
				b[++tot].x=Q[i].x;b[tot].idx=i;b[tot].type=2;
			}
	}
	sort(b+1,b+1+tot,cmp);
	cnt=1;
	if (b[1].type==1){ys[cnt]=a[b[1].idx].x;a[b[1].idx].x=1;}
	else {ys[cnt]=Q[b[1].idx].x;Q[b[1].idx].x=1;}
	rep(i,2,tot)
		if (b[i].x==b[i-1].x){
				if (b[i].type==1){
					    ys[cnt]=a[b[i].idx].x;
						a[b[i].idx].x=cnt;
				}
				else {
					ys[cnt]=Q[b[i].idx].x;
					Q[b[i].idx].x=cnt;
				}
		}
		else {
				if (b[i].type==1){
						 ys[++cnt]=a[b[i].idx].x;
						a[b[i].idx].x=cnt;
				}
				else {
					ys[++cnt]=Q[b[i].idx].x;
					Q[b[i].idx].x=cnt;
				}
		}
}
void ins(int o){
	int st=root[o-1],now,w,x=a[o].x;
	now=root[o]=++tot;t[now].sum++;
	dto(i,maxw,0){
		w=(x>>i)&1;
		t[now].son[w]=++tot;
		now=t[now].son[w];
		st=t[st].son[w];
		t[now]=t[st];
		t[now].sum++;
	}
	t[now].num=a[o].x;
}
void bt(){
	tot=0;root[0]=0;
	t[0].sum=t[0].son[0]=t[0].son[1]=t[tot].num=0;
	rep(i,1,n)ins(i);
	rot[0]=++tot;
	t[tot].sum=t[tot].son[0]=t[tot].son[1]=t[tot].num=0;
	rep(i,1,n){
		rot[i]=++tot;
		t[rot[i]]=t[rot[i-1]];
	}
}
void updata(int now,int x,int val){
	int w;
	t[now].sum+=val;
	dto(i,maxw,0){
		w=(x>>i)&1;
		if (!t[now].son[w]){
			t[now].son[w]=++tot;
			t[t[now].son[w]].num=0;
			t[t[now].son[w]].sum=0;
		}
		now=t[now].son[w];
		t[now].sum+=val;
	}
	t[now].num=x;
}
void change(int w,int x,int val){
	for (;w<=n;w+=lowbit(w))
	     updata(rot[w],x,val);
}
void query(int l,int r,int k){
	int ll=l,rr=r,tl,tr,type,ans;
	Left[0]=Right[0]=0;
	for (;ll>0;ll-=lowbit(ll))Left[++Left[0]]=rot[ll];
	for (;rr>0;rr-=lowbit(rr))Right[++Right[0]]=rot[rr];
	l=root[l],r=root[r];
	dto(i,maxw,0){
		tl=t[t[l].son[0]].sum;tr=t[t[r].son[0]].sum;
		rep(j,1,Left[0])tl+=t[t[Left[j]].son[0]].sum;
		rep(j,1,Right[0])tr+=t[t[Right[j]].son[0]].sum;
		if (tr-tl>=k)type=0;
		else type=1;
		k-=type*(tr-tl);
		l=t[l].son[type];r=t[r].son[type];
		rep(j,1,Left[0])Left[j]=t[Left[j]].son[type];
		rep(j,1,Right[0]){
			Right[j]=t[Right[j]].son[type];
			if (t[Right[j]].num)ans=ys[t[Right[j]].num];
		}
	}
	if (t[r].num)ans=ys[t[r].num];
	printf("%d\n",ans);
}
void solve(){
	rep(i,1,m){
		if (s[i][0]=='Q')query(Q[i].l-1,Q[i].r,Q[i].x);
		else {
			change(Q[i].l,a[Q[i].l].x,-1);
			change(Q[i].l,Q[i].x,1);
			a[Q[i].l].x=Q[i].x;
		}
	}
}
int main(){
	int T;
	freopen("dynamic.in","r",stdin);
	freopen("dynamic.out","w",stdout);
	scanf("%d",&T);
	while (T--){
		memset(t,0,sizeof(t));
		init();
		bt();
		solve();
	}
}