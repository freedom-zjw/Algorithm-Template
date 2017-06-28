/*
 一个背包总容量为M，现在有6个物品，第i个 物品体积为w[i]，
价值为v[i]，每个物品都有A[i]，现在往背包里面装东西，
怎么装能使背包的内物品价值最大？
 */
#include<iostream>
#include<cstring>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
#define dto(i,u,v) for (int i=(u);i>=(v);i--)
const int w[]={3,5,2,6,11,8};
const double v[]={0.01,0.05,0.10,0.25,0.50,1.00};
int a[6];
double f[10010];
int main(){
    int M;
    while (cin>>M){
        rep(i,0,5)cin>>a[i];
        memset(f,0,sizeof(f));
        rep(i,0,5){
            if (a[i]*w[i]>M){
                rep(j,w[i],M)
                    f[j]=max(f[j],f[j-w[i]]+v[i]);  
            }
            else {
                int k=1;
                while (k<a[i]){
                    dto(j,M,k*w[i])
                        f[j]=max(f[j],f[j-k*w[i]]+k*v[i]);
                    a[i]-=k;
                    k*=2;
                }   
                dto(j,M,a[i]*w[i])
                    f[j]=max(f[j],f[j-a[i]*w[i]]+a[i]*v[i]);
            }
        }
        printf("$%.2lf\n",f[M]);
    }
    return 0;
}                             