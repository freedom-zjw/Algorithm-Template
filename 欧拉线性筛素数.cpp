#include<iostream>
#include<cstring>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
int p[80000],v[1000001],a[110];
int tot;
void init(){
	rep(i,2,1000000){
		if (!v[i])p[++tot]=i;
		for (int j=1;j<=tot;j++){
			if ((long long)p[j]*i>1000000)break;
			v[p[j]*i]=1;
			if (i%p[j]==0)break;
		}
	}
}