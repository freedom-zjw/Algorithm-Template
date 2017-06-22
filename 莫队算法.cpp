#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 50010
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
struct node{
    int l,r,idx;
    long long a,b;
}ask[N],ans[N];
int n,m,mm,tot;
int c[N],s[N],block[N];
bool cmp(node n1,node n2){
    return block[n1.l]<block[n2.l]||(block[n1.l]==block[n2.l]&&n1.r<n2.r);
}
void init(){
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%d",&c[i]);
    rep(i,1,m){
        scanf("%d%d",&ask[i].l,&ask[i].r);
        ask[i].idx=i;
    }
    mm=(int)sqrt(n*1.0);
    rep(i,1,n)block[i]=(i-1)/mm+1;
    sort(ask+1,ask+1+m,cmp);
}
/*sigma(S[i]*(S[i]-1)/2)/[(r-l+1)*(r-l)/2]
   =sigma(S[i]*(S[i]-1))/[(r-l+1)*(r-l)]
   =[sigma(S[i]*S[i])-(r-l+1)]/[(r-l+1)*(r-l)]
*/
long long gcd(long long x,long long y){
    if (!y)return x;
    else return gcd(y,x%y);
}
void caln(int p,int delta){
    tot-=s[c[p]]*s[c[p]];
    s[c[p]]+=delta;
    tot+=s[c[p]]*s[c[p]];
}
void solve(){
    int l=1,r=0;tot=0;long long k;
    rep(i,1,m){
        if (r<ask[i].r){
            for (r=r+1;r<=ask[i].r;r++)caln(r,1);
            r--; 
        }
        else if (r>ask[i].r){
            for (;r>ask[i].r;r--)caln(r,-1);
        }
        if (l<ask[i].l){
            for (;l<ask[i].l;l++)caln(l,-1);
        }
        else if (l>ask[i].l){
            for (l=l-1;l>=ask[i].l;l--)caln(l,1);
            l++;
        }
        if (l==r){
            ans[ask[i].idx].a=0;ans[ask[i].idx].b=1;
            continue;
        }
        ans[ask[i].idx].a=tot-(r-l+1);
        ans[ask[i].idx].b=(long long)(r-l+1)*((long long)(r-l));
        k=gcd(ans[ask[i].idx].a,ans[ask[i].idx].b);
        ans[ask[i].idx].a/=k;
        ans[ask[i].idx].b/=k;
    }
    rep(i,1,m)printf("%lld/%lld\n",ans[i].a,ans[i].b);
}
int main(){ 
    init();
    solve();
    return 0;
} 