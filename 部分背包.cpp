/*
问题描述：n件物品，第i件物品价值 vi 元，重wi 磅。
希望用 W磅的背包 拿走最重的物品。第i件物品可以都拿走，
也可以拿走一部分。（物品可以分割所以称为部分背包）
 */
#include<cstdio>
#incldue<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
int main(){
	int w[1000],v[1000];//w为质量，v为价值，r为价值与质量的比
	float r[1000];//r为价值与质量的比
	int n;//物品的数量
	int m; //背包的容量 
	scanf("%d %d",&m,&n);   //输入背包总量和数量
	for(int i=0;i<n;i++){
		scanf("%d %d",&w[i],&v[i]);
		r[i]=v[i]*1.0/w[i];
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<n-i;j++){
			if(r[j]<r[j+1]){
				swap(r[j],r[j+1]);
				swap(w[j],w[j+1]);
				swap(v[j],v[j+1]);
			} 
		} 
	}
	int i=0;
	while(m>0){
		if(w[i]<=m){
			m-=w[i];
			printf("价值：%d取：%d\n",v[i],w[i]);
			i++;
		}
		else{
			printf("价值：%d取：%d\n",v[i],m);
			m=0;
		}
	} 
	return 0;
} 
