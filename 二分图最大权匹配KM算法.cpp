/*
���Ȿ������n���˶�n����Ʒ������һ������ȣ�������Ʒ�����������Ⱥ�
����ͼ���Ȩƥ�� 
ss*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib> 
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
#define N 20
#define INF 1000000000;
int lx[N],ly[N],vx[N],vy[N];
int match[N],slack[N],weight[N][N];
int n;
int findpath(int x){
	vx[x]=1;
	rep(y,1,n){
		if (!vy[y]){
			int temp=lx[x]+ly[y]-weight[x][y];
			if (!temp){
				vy[y]=1;
				if (match[y]==-1||findpath(match[y])){
					match[y]=x;
					return 1;
				}
			}
			else slack[y]=slack[y]>temp?temp:slack[y];
		}
	}
	return 0;
}
int main(){
	int T;
	cin>>T;
	rep(tt,1,T){
		cin>>n;
		memset(match,-1,sizeof(match));
		memset(lx,0,sizeof(lx));
		memset(ly,0,sizeof(ly));
		rep(i,1,n)
			rep(j,1,n){
				cin>>weight[i][j];
				if (lx[i]<weight[i][j])
					lx[i]=weight[i][j];
			}
			
		rep(i,1,n){
			rep(j,1,n)slack[j]=INF;
			while (1){
				memset(vx,0,sizeof(vx));
				memset(vy,0,sizeof(vy));
				if (findpath(i))break;//����ҵ� ƥ�䣬Ϊ��һ������ƥ�� 
				//�����޸ı��ֵʹ���µı߼��������ͼ 
				int inc=INF;
				rep(j,1,n){
					if (!vy[j]&&slack[j]<inc)
						inc=slack[j];
				}
				rep(j,1,n){
					if (vx[j])lx[j]-=inc;
					if (vy[j])ly[j]+=inc;
				}
			}
		}
		int ans=0;
		rep(j,1,n)
				if (match[j]!=-1)
					ans+=weight[match[j]][j];
			cout<<ans<<endl;	
	}
	return 0;
}