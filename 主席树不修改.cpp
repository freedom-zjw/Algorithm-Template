#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
#define reph(k,x) for (int k=first[x];k;k=edge[k].next)
#define dto(i,u,v) for (int i=(u);i>=(v);i--)
#define lowbit( x ) ( ( x ) & ( - ( x ) ) )
#define N 80010
#define maxw 18
struct node{int y,next;}edge[N*2];
struct tree{int son[2],sum,num;}t[N*2*25];
struct ques{int k,x,y;}Q[N];
struct lsh{int type,idx,d;}b[N*2];
int n,m,len,tot,cnt;
int list[N],a[N],first[N],ys[N*2],Begin[N],End[N];
int dep[N],fa[N][21],root[N],rot[N],Left[2*N],Right[2*N];
void ins(int x,int y){
	edge[++len].y=y;edge[len].next=first[x];first[x]=len;
}
bool cmp(lsh n1,lsh n2){return n1.d<n2.d;}
inline void Lisan(){
	sort(b+1,b+1+tot,cmp);
	cnt=1;ys[1]=b[1].d;
	if (!b[1].type)a[b[1].idx]=1;
	else Q[b[1].idx].y=1;
	rep(i,2,tot){
		if (b[i].d!=b[i-1].d){cnt++;ys[cnt]=b[i].d;}
		if (!b[i].type)a[b[i].idx]=cnt;
	    else Q[b[i].idx].y=cnt;
	}
}
inline void bt(int o,int pre){
	int now,st=root[pre],x;
	now=root[o]=++tot;
	t[now]=t[st];t[now].sum++;
	dto(i,maxw,0){
		x=(a[o]>>i)&1;
		t[now].son[x]=++tot;
		now=t[now].son[x];
		st=t[st].son[x];
		t[now]=t[st];
		t[now].sum++;
	}
	t[now].num=a[o];
}
inline void dfs(int x,int pre){
	list[++list[0]]=x;Begin[x]=list[0];
	bt(x,pre);
	rep(i,1,maxw){
		if (dep[x]<=(1<<i))break;
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	reph(k,x){
		int y=edge[k].y;
		if (y!=pre){
			dep[y]=dep[x]+1;
			fa[y][0]=x;
			dfs(y,x);
		}
	}
	End[x]=list[0];
}
inline void init(){
	int x,y;tot=0;list[0]=0;
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%d",&a[i]);
		b[++tot].d=a[i];
		b[tot].idx=i;b[tot].type=0;
	}	
	rep(i,1,n-1){
		scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	rep(i,1,m){
		scanf("%d%d%d",&Q[i].k,&Q[i].x,&Q[i].y);
		if (!Q[i].k){
			b[++tot].d=Q[i].y;
			b[tot].idx=i;b[tot].type=1;
		}
	}
	Lisan();tot=0;dep[0]=-1;
	dep[1]=0;dfs(1,0);
	rep(i,1,n)rot[i]=++tot;
}
inline void updata(int now,int x,int val){
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
inline void change(int w,int x,int val){
	for (;w<=n;w+=lowbit(w))updata(rot[w],x,val);
}
inline int LCA(int x,int y){
   if (dep[x]<dep[y])swap(x,y);
   dto(i,maxw,0)
      if (dep[x]-dep[y]>=(1<<i))
         x=fa[x][i];
   if (x==y)return x;
   dto(i,maxw,0)
      if (dep[x]>(1<<i)&&fa[x][i]!=fa[y][i])
      {   x=fa[x][i];
          y=fa[y][i];
      }
   return fa[x][0];
}
inline void get(int x,int type){
	if (!type)for (;x>0;x-=lowbit(x))Left[++Left[0]]=rot[x];
	else for (;x>0;x-=lowbit(x))Right[++Right[0]]=rot[x];
}
inline void query(int x,int y,int dad,int k){
	int tl=0,tr=0,ans,type;
	Right[0]=Left[0]=0;
	Right[++Right[0]]=root[x];
	Right[++Right[0]]=root[y];
	Left[++Left[0]]=root[dad];
	Left[++Left[0]]=root[fa[dad][0]];
	get(Begin[x],1);get(Begin[y],1);get(Begin[dad],0);get(Begin[fa[dad][0]],0);
	dto(i,maxw,0){
		tr=tl=0;
		rep(j,1,Left[0])tl+=t[t[Left[j]].son[1]].sum;
		rep(j,1,Right[0])tr+=t[t[Right[j]].son[1]].sum;
		if (tr-tl>=k)type=0;
		else type=1;
		k-=type*(tr-tl);
		rep(j,1,Left[0])Left[j]=t[Left[j]].son[type^1];
		rep(j,1,Right[0]){
			Right[j]=t[Right[j]].son[type^1];
			if (t[Right[j]].num)ans=ys[t[Right[j]].num];
		}
	}
	printf("%d\n",ans);
}
inline void solve(){
	rep(i,1,m){
		if (!Q[i].k){
			change(Begin[Q[i].x],a[Q[i].x],-1);
			change(End[Q[i].x]+1,a[Q[i].x],1);
			change(Begin[Q[i].x],Q[i].y,1);
			change(End[Q[i].x]+1,Q[i].y,-1);
			a[Q[i].x]=Q[i].y;
		}
		else {
			int dad=LCA(Q[i].x,Q[i].y);
			if (dep[Q[i].x]+dep[Q[i].y]-dep[dad]-dep[fa[dad][0]]<Q[i].k)printf("invalid request!\n");
			else query(Q[i].x,Q[i].y,dad,Q[i].k);
		}
	}
}
int main(){
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	init();
	solve();
}