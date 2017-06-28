/*
一个背包总容量为V，现在有N个物品，第i个 物品体积为weight[i]，
价值为value[i]，每个物品都有无限多件，现在往背包里面装东西，
怎么装能使背包的内物品价值最大？
 */
#include<iostream>  
using namespace std;  
#define  V 1500  
unsigned int f[V];//全局变量，自动初始化为0  
unsigned int weight[10];  
unsigned int value[10];  
#define  max(x,y)   (x)>(y)?(x):(y)  
int main()  
{  
      
    int N,M;  
    cin>>N;//物品个数  
    cin>>M;//背包容量  
    for (int i=1;i<=N; i++)  
    {  
        cin>>weight[i]>>value[i];  
    }  
    for (int i=1; i<=N; i++)  
        for (int j=1; j<=M; j++)  
        {  
            if (weight[i]<=j)  
            {  
                f[j]=max(f[j],f[j-weight[i]]+value[i]);  
            }             
        }  
      
    cout<<f[M]<<endl;//输出最优解  
  
}  