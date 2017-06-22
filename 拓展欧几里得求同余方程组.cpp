/*
解同余方程组：
x≡r1(moda1)x≡r2(moda2)......x≡rn(modan)
其中模数不一定互质。
题解
若模数两两互质，我们可以用中国剩余定理来解。 
这里我们先考虑两个方程：
x≡r1(moda1)x≡r2(moda2)
我们可以写成:
x+y1a1=r1x−y2a2=r2
相减得：y1a1+y2a2=r1−r2也就是ax+by=m的形式。 
这是可以用扩展欧几里德解的。 
若gcd(a,b)/|m那么方程就无解，直接输出-1。 
否则我们可以解出上式的y1。回带得到一个特解x0=r1−y1a1。 
通解可以写成x=x0+k∗lcm(a1,a2)也就是x≡x0(modlcm(a1,a2))。 
这样我们就将两个方程合并为了一个。重复进行以上操作，我们最终能将n个方程全部合并，再用扩展欧几德得解出来就好了。
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a[100005],r[100005];
int n;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0) return x=1,y=0,a;
    ll tmp=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return tmp;
}
ll solve(){
    ll M=a[1],R=r[1],x,y,d;
    for(int i=2;i<=n;i++){
        d=exgcd(M,a[i],x,y);
        if((R-r[i])%d!=0) return -1;
        x=(R-r[i])/d*x%a[i];
        R-=x*M;
        M=M/d*a[i];
        R%=M;
    }
    return (R%M+M)%M;
}
int main(){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&r[i]);
        printf("%lld\n",solve());
    }
    return 0;
}