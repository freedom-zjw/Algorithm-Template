/*
找出一个字符串中至少重复出现两次的字串的个数，注意重复出现时不能有重叠的现象
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define dto(i,a,b) for (int i=a;i>=b;i--)
#define maxn 1205
int n,r[maxn],wr[maxn],rs[maxn],h[maxn],a[maxn],y[maxn],sa[maxn];
char str[maxn];
int minn(int x,int y){return x>y?y:x;}
int maxx(int x,int y){return x>y?x:y;}
bool cmp(int k1,int k2,int ln){return wr[k1]==wr[k2]&&wr[k1+ln]==wr[k2+ln];}
void get_sa(int m)
{   memcpy(r,a,sizeof(a));
    rep(i,0,m)rs[i]=0;
    rep(i,1,n)rs[r[i]]++;
    rep(i,1,m)rs[i]+=rs[i-1];
    dto(i,n,1)sa[rs[r[i]]--]=i;
    int p=0,ln=1,k;
    while (p<n){k=0;
        rep(i,n-ln+1,n)y[++k]=i;
        rep(i,1,n)if (sa[i]>ln)y[++k]=sa[i]-ln;
        rep(i,1,n)wr[i]=r[y[i]];
        rep(i,0,m)rs[i]=0;
        rep(i,1,n)rs[wr[i]]++;
        rep(i,1,m)rs[i]+=rs[i-1];
        dto(i,n,1)sa[rs[wr[i]]--]=y[i];
        memcpy(wr,r,sizeof(r));
        p=1;r[sa[1]]=1;
        rep(i,2,n){
       	   if (!cmp(sa[i-1],sa[i],ln))p++;
       	   r[sa[i]]=p;
        }
        m=p;ln*=2;
    }
}
void makeheight()
{   int k=0,j;
    rep(i,1,n){
    	 j=sa[r[i]-1];
    	 if (k)k--;
    	 while (a[i+k]==a[j+k])k++;
    	 h[r[i]]=k;
    }
}
int main()
{   int ans;
    while (1)
    {       scanf("%s",str+1);if (str[1]=='#')break;
	        n=strlen(str+1);int l,r;
            rep(i,1,n)a[i]=str[i];a[n+1]=0;
            get_sa(256);makeheight();ans=0;
            rep(i,1,n/2){
			      l=1200;r=-1;
            	  rep(j,1,n){
            	  	   if (h[j]>=i){
            	  	   	    l=minn(l,sa[j-1]);r=maxx(r,sa[j-1]);
            	  	   	    l=minn(l,sa[j]);r=maxx(r,sa[j]);
            	  	   }
            	  	   else {if (r!=-1&&l+i<=r)ans++;l=1200;r=-1;}
            	  }
				  if (r!=-1&&l+i<=r)ans++;
            }
            printf("%d\n",ans);
    }
	return 0;
}