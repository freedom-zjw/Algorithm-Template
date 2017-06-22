/*
�ж��������� i<=k�� 2^i-1 �Ƿ������������ǵĻ���Ҫ�����ֽ���
�����������
k<=63
 */
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
typedef long long ll;
ll fac[110];
int tot;
int isPrime(int x){
	if (x==2)return 1;
	rep(i,2,(int)sqrt(x))
		if (x%i==0)return 0;
	return 1;
}
//����-������������
ll qmul(ll a,ll b,ll c){//���ٳ˷�a*b%c 
	a%=c;b%=c;
	ll ans=0;
	while (b){
		if (b&1)ans=(ans+a)%c;
		a=(a<<1)%c;
		b>>=1;
	}
	return ans;
}
ll qpow(ll a,ll b,ll c){//������a^b % c 
	if (b==1)return a%c;
	if (!b)return 1%c;
	ll tmp=qpow(a,b/2,c);
	tmp=qmul(tmp,tmp,c);
	if (b&1)tmp=qmul(tmp,a,c);
	return tmp;
}
int check(ll a,ll d,int r,ll n){
//��֤a^(d*2^r) %n=1 �� n-1
	ll tmp=qpow(a,d,n);
	ll last=tmp;
	rep(i,1,r){
		tmp=qmul(tmp,tmp,n);
		if (tmp==1&&last!=1&&last!=n-1)return false;
		last=tmp;
	}
	if (tmp!=1)return false;
	return true;
}
int Miller_Rabin(ll n){
	if ( n<2 || n&1==0 )return 0;
	if (n==2)return 1;
	ll d=n-1; int r=0;
	while ( (d&1)==0 )d>>=1,r++; //��n�ֽ��d*2^r 
	rep(i,1,30){//�������30�Σ���С�������
		ll a=rand()%(n-1)+1; 
		if (!check(a,d,r,n))return false;//��ͨ���������Ǻ��� 
	}
	return true; 
}
/////////////////// 
///Pollard_rho�������������ֽ�
ll gcd(ll a,ll b){
	if (a<0)a=-a;
	if (b<0)b=-b;
	if (!b)return a;
	else return gcd(b,a%b); 
}
ll Pollard_rho(ll x,ll c){
	ll i=1,k=2;  
    ll x0=rand()%x;  
    ll y=x0;  
    while(1){  
        i++;  
        x0=(qmul(x0,x0,x)+c)%x;  //x^2+c
        ll d=gcd(y-x0,x);  
        if(d!=1&&d!=x) return d;  
        if(y==x0) return x;  //�ҵ�ѭ�����㷨ʧ�ܣ����� 
        if(i==k){y=x0;k+=k;} //����y��Ѱ�ҷ�Χ����2������һ���Ż� 
    } 
}
void findfac(ll n){
	if (Miller_Rabin(n)){
		fac[++tot]=n;
		return;
	}
	ll p=n;
	while (p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
	findfac(p); //�ҵ���һ�����ӣ���ô�ݹ���ȥ������ 
	findfac(n/p);
}
/////////////////////////////
void work(int k){
	ll n=(1LL<<(k))-1;
    tot=0;
	findfac(n);
	if (tot>1){ 
		sort(fac+1,fac+tot+1);
		printf("%lld",fac[1]);
		rep(i,2,tot) printf(" * %lld",fac[i]);  
 		printf(" = %lld = ( 2 ^ %d ) - 1\n", n, k);
	}
}
int main(){
	srand(1996-04-22); 
	int k;
	scanf("%d",&k);
	rep(i,2,k)
		if (isPrime(i))
				work(i);
	return 0;
}