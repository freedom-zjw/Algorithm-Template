#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stack>
#include<map>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
struct BigNum{
    const static int Maxn=1100,exp=16,remain=2;//expΪ����10λ��remain�Ǳ���2λС�� 
    int v[Maxn],flag;//flag=0,������flag=1���� 
    BigNum(int n=0 ){//����ת�� 
        memset(v,0,sizeof(v));
        v[0]=exp; 
        if (n<0)n=-n,flag=1;
        else flag=0;
        do{
            v[++v[0]]=n%10;
            n/=10;
        }while(n>0);
    }
    BigNum(string str){//�ַ���ת�� 
        memset(v,0,sizeof(v));
        if (str[0]=='-')flag=1,str.erase(0,1);
        else flag=0;
        int len=str.size(),pos=-1;
        for (int i=1;i<len;i++)
        	if (str[i]=='.'){
        		pos=i;
        		break;
			}
        v[0]=str.size()+exp;
        if (pos!=-1)v[0]-=(len-pos);
        for(int i=1;i<=v[0]-exp;i++)v[i+exp]=str[v[0]-exp-i]-48;
        if (pos!=-1)
        	for (int i=pos+1;i<len;i++)v[exp+1-(i-pos)]=str[i]-48; 
		while (v[v[0]]==0&&v[0]>exp+1)v[0]--;      	
    }    
    bool operator <= (const BigNum & y){
        BigNum & x = * this;
        if(x.v[0]!=y.v[0])    return x.v[0]<y.v[0];
        for(int i=x.v[0];i>0;i--)
            if(x.v[i]<y.v[i])return true;
            else if(x.v[i]>y.v[i])    return false;
        return true;
    }
    bool operator == (const BigNum & y){
        BigNum & x = * this;
        if(x.v[0]!=y.v[0])    return false;
        for(int i=x.v[0];i>0;i--)
            if(x.v[i]!=y.v[i])return false;
        return true;
    }
    BigNum operator + (const BigNum & y){//�߾���+ 
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
    BigNum operator - (const BigNum & y){//�߾���- 
        BigNum & x = * this;
        BigNum c;
        for(int i=1;i<=x.v[0];i++){
            c.v[i]+=x.v[i]-y.v[i];
            if(c.v[i]<0)c.v[i+1]--,c.v[i]+=10;
        }
        c.v[0]=x.v[0];
        while((c.v[c.v[0]]==0)&&(c.v[0]>exp+1))c.v[0]--;
        return c;
    }
    BigNum operator / (const int & y){//�߾�/����
        BigNum x = * this ;
        BigNum c=x;
        int i,tt=0,yy=y;
        if(y<0)tt=1,yy=-y;
        for (int i=c.v[0];i>=1;i--){
            if (i-1>0){
                int ret=c.v[i-1];
                c.v[i-1]=(c.v[i]%yy)*10+ret;
            }
            c.v[i]=c.v[i]/2;
        }
        while((c.v[c.v[0]]==0)&&(c.v[0]>exp+1))c.v[0]--;
        c.flag=x.flag^tt;
        return c;
    }
    BigNum operator * (const BigNum & y){//�߾�*�߾� 
        BigNum x = * this ;BigNum c;
        int i,j;
        c.v[0]=x.v[0]+y.v[0]-1;
        for(i=1;i<=x.v[0];i++)
            for(j=1;j<=y.v[0];j++)
                if (i+j-1-exp>0)
                    c.v[i+j-1-exp]+=x.v[i]*y.v[j];
        i=1;
        for(; c.v[i]||i<=c.v[0] ; i++ )c.v[i+1]+=c.v[i]/10,c.v[i]%=10;
        c.v[0]=i-1;
        while((c.v[c.v[0]]==0)&&(c.v[0]>exp+1))c.v[0]--;
        c.flag=x.flag^y.flag;
        return c;
    }
    BigNum operator / ( BigNum & y){//�߾�/�߾�
        BigNum x = * this ;
        BigNum c,tmp,one;
        one.v[1]=1;
        if (x==y)c=BigNum(1);
        else {
            BigNum L,R,Mid;
            string s0="1";
			if (y.v[0]==exp+1&&y.v[exp+1]==0){
				for (int i=exp;i>=1;i--){
					s0+="0";
					if (v[i]!=0)break;
				}
			}
			if (s0!="1")x=x*BigNum(s0),y=y*BigNum(s0);
            if (x<=y)R=y;
            else R=x;
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
    BigNum operator % (BigNum & y){//�߾�%�߾�
        BigNum x = * this ;
        BigNum c,tmp,one;
        one.v[exp+1]=1;
        if (x==y)return c;
        else if (x<=y)return x;
		else  {
            BigNum L,R,Mid,yy=y,xx=x;
            L.v[exp+1]=1;
            string s0="1";
			if (y.v[0]==exp+1&&y.v[exp+1]==0){
				for (int i=exp;i>=1;i--){
					s0+="0";
					if (v[i]!=0)break;
				}
			}
			if (s0!="1")x=x*BigNum(s0),y=y*BigNum(s0);
            if (x<=y)R=y;
            else R=x;
            while (L<=R){
                Mid=(L+R)/2;
                for (int i=1;i<=exp;i++)Mid.v[i]=0;
                tmp=Mid*y;
                if (tmp<=x){
                    c=Mid;
                    L=Mid+one;
                }
                else R=Mid-one;
            }
        	c=xx-c*yy;
			c.flag=x.flag;
		}
        return c;
    }
    void Print(){
        int i;
        if (flag)printf("-");
        if (v[exp-remain]>=5){
            v[exp-remain+1]++;
            for(i=exp-remain+1;v[i]||i<=v[0];i++){
                v[i+1]+=v[i]/10;
                v[i]%=10;
            }
            v[0]=i-1;
        }
        for(i=v[0];i>exp;i--)printf("%d",v[i]);
        printf(".");
        for (i=exp;i>=exp-remain+1;i--)printf("%d",v[i]); 
        printf("\n");
    }
}zero;
BigNum calc(BigNum r1,char ch,BigNum r2){//������֮������� 
    BigNum Result;
    if (ch=='+'){
        if (r1.flag^r2.flag==0)Result=r1+r2,Result.flag=r1.flag;
        else {
            if (r1.flag==1){
                if (r1<=r2)Result=r2-r1,Result.flag=0;
                else Result=r1-r2,Result.flag=1;
            }
            else {
                if (r1<=r2)Result=r2-r1,Result.flag=1;
                else Result=r1-r2,Result.flag=0;
            }
        }
    }
    else if (ch=='-'){
        if (r1.flag==0&&r2.flag==0){
            if (r1<=r2)Result=r2-r1,Result.flag=1;
            else Result=r1-r2,Result.flag=0;
        }
        else if(r1.flag==1&&r2.flag==1){
            if (r1<=r2)Result=r2-r1,Result.flag=0;
            else Result=r1-r2,Result.flag=1;
        }
        else Result=r1+r2,Result.flag=r1.flag;
    }
    else if (ch=='*')return r1*r2;
    else if (ch=='/')return r1/r2;
    else if (ch=='%')return r1%r2;
    return Result;
}
int main(){
	string s1,s2;
	int x;
	cin>>s1>>x;
	BigNum ans;
    /*ans=BigNum(s1)+BigNum(s2);
    ans.Print();
	ans=BigNum(s1)-BigNum(s2);
    ans.Print();
	ans=BigNum(s1)*BigNum(s2);
	ans.Print();*/
	ans=BigNum(s1)/BigNum(2);
	ans.Print();
	ans=ans*BigNum(2); 
	ans.Print();
}