#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
struct BigNum{
	const static int Maxn=610;
	int v[Maxn],flag;//flag=0正数 flag=1负数 
	BigNum(int n=0 ){//数字转化
		memset(v,0,sizeof(v));
		if (n<0)n=-n,flag=1;
		else flag=0;
		do{
			v[++v[0]]=n%10;
			n/=10;
		}while(n>0);
	}
	BigNum(string str){//字符串转化
		memset(v,0,sizeof(v));
		if (str[0]=='-')flag=1,str.erase(0,1);
		else flag=0;
		v[0]=str.size();
		for(int i=1;i<=v[0];i++)v[i]=str[v[0]-i]-48;
	}	
	bool operator <= (const BigNum & y){
		BigNum & x = * this;
		if(x.v[0]!=y.v[0])	return x.v[0]<y.v[0];
		for(int i=x.v[0];i>0;i--)
			if(x.v[i]<y.v[i])return true;
			else if(x.v[i]>y.v[i])	return false;
		return true;
	}
	bool operator == (const BigNum & y){
		BigNum & x = * this;
		if(x.v[0]!=y.v[0])	return false;
		for(int i=x.v[0];i>0;i--)
			if(x.v[i]!=y.v[i])return false;
		return true;
	}
	BigNum operator + (const BigNum & y){//高精度+
		BigNum & x = * this;
		BigNum c;
		int i;
		c.v[0]=max(x.v[0],y.v[0]);
		for(i=1;i<=c.v[0];i++){
			c.v[i]+=x.v[i]+y.v[i];
			c.v[i+1]=c.v[i]/10;
			c.v[i]%=10;
		}
		for(;c.v[i];i++)c.v[i+1]=c.v[i]/10,c.v[i]%=10;
		c.v[0]=i-1;
		return c;
	}	
	BigNum operator - (const BigNum & y){//高精度-
		BigNum & x = * this;
		BigNum c;
		for(int i=1;i<=x.v[0];i++){
			c.v[i]+=x.v[i]-y.v[i];
			if(c.v[i]<0)	c.v[i+1]--,c.v[i]+=10;
		}
		c.v[0]=x.v[0];
		while((c.v[c.v[0]]==0)&&(c.v[0]>1))	c.v[0]--;
		return c;
	}
	BigNum operator * (const int & y){//高精*单精
		BigNum x = * this ;
		BigNum c;
		int i,tt=0;
		if(y<0)tt=1;
		for(i=1;i<=x.v[0];i++){
			c.v[i]+=x.v[i]*y;
			c.v[i+1]=c.v[i]/10;
			c.v[i]%=10;
		}
		for(;c.v[i];i++)c.v[i+1]=c.v[i]/10,c.v[i]%=10;
		while((c.v[c.v[0]]==0)&&(c.v[0]>1))	c.v[0]--;
		c.flag=x.flag^tt;
		return c;
	}
	BigNum operator / (int & y){//高精/单精
		BigNum x = * this ;
		BigNum c=x;
		int i,tt=0;
		if(y<0)tt=1,y=-y;
		for (int i=c.v[0];i>=1;i--){
			if (i-1>0){
				int ret=c.v[i-1];
				c.v[i-1]=(c.v[i]%y)*10+ret;
			}
			c.v[i]=c.v[i]/2;
		}
		while((c.v[c.v[0]]==0)&&(c.v[0]>1))	c.v[0]--;
		c.flag=x.flag^tt;
		return c;
	}
	BigNum operator * (const BigNum & y){//高精*高精
		BigNum x = * this ;BigNum c;
		int i,j;
		c.v[0]=x.v[0]+y.v[0]-1;
		for(i=1;i<=x.v[0];i++)
			for(j=1;j<=y.v[0];j++)
				c.v[i+j-1]+=x.v[i]*y.v[j];
		i=1;
		for(; c.v[i]||i<=c.v[0] ; i++ )c.v[i+1]+=c.v[i]/10,c.v[i]%=10;
		c.v[0]=i-1;
		while((c.v[c.v[0]]==0)&&(c.v[0]>1))c.v[0]--;
		c.flag=x.flag^y.flag;
		return c;
	}
	BigNum operator / (const BigNum & y){//高精/高精
		BigNum x = * this ;
		BigNum c,tmp,one(1);
		if (x.v[0]==1&&x.v[1]==0)c=x;
		else if (x==y)c=BigNum(1);
		else if (x<=y)c=BigNum(0);
		else {
			BigNum L(1),R,Mid;
			R=x;
			while (L<=R){
				Mid=(L+R)/2;
				tmp=Mid*y;
				if (tmp<=x){
					c=Mid;
					L=Mid+one;
				}
				else R=Mid-one;
			}
			c.flag=x.flag^y.flag;
		}
		return c;
	}
	void Print(){
		if (flag)cout<<"-";
		for(int i=v[0];i>0;i--)printf("%d",v[i]);
		printf("\n");
	}
};
int main(){
	string s1,s2;
	cin>>s1>>s2;
	BigNum ans;
    ans=BigNum(s1)+BigNum(s2);
    ans.Print();
	ans=BigNum(s1)-BigNum(s2);
    ans.Print();
	ans=BigNum(s1)*BigNum(s2);
	ans.Print();
	ans=BigNum(s1)/BigNum(s2);
	ans.Print();
}