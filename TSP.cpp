/*
�б��1��N��N�����У��ʴ�1�ų��г�����
���������еĳ��в����ͣ����N�ų��е����·�����ȡ�
*/
#include <bits/stdc++.h>  
const double INF=10e7;  
using namespace std;  
int T,n,cnt;  
double a[25][25],dp[25][1100000];   
struct point{       //���ṹ��   
    int x,y;  
}pt[25];   
double d(point a,point b){      //�������   
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));  
}  
int main()  {  
    scanf("%d",&T);  
    while(T--){  
        cnt=1;  
        scanf("%d",&n);  
        for(int i=2;i<n;i++) cnt<<=1;      //�������������յ��⣩          
        for(int i=0;i<n;i++)             //����   
            scanf("%d %d",&pt[i].x,&pt[i].y);         
        for(int i=0;i<n;i++)             //����   
            for(int j=0;j<n;j++)  
                a[i][j]=d(pt[i],pt[j]);  
                  
        for(int i=0;i<n;i++)             //��ʼ��   
            for(int j=0;j<cnt;j++)  
                dp[i][j]=INF;  
          
        for(int i=0;i<n;i++)             //���ȷ�������³�ʼ����   
            dp[i][0]=a[i][0];                 
        for(int i=1;i<cnt;i++)               //����Ԫ�ؿ�����   
            for(int j=1;j<n-1;j++){    
                for(int k=1;k<n-1;k++)  {  
                    if((1<<k-1)&i)        //k is in the set  
                        dp[j][i]=min(dp[j][i],a[j][k]+dp[k][i-(1<<k-1)]); //״̬ת�Ʒ���   
                }  
            }  
        double ans=INF;  
        for(int i=1;i<n;i++)  
            ans=min(ans,dp[i][cnt-1]+a[i][n-1]);  
        printf("%.2lf\n",ans);  
    }    
    return 0;  
}                    