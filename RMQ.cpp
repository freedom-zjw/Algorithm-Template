#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 50010
#define Max(x,y) (x>y?x:y)
#define Min(x,y) (x>y?y:x)
int maxsum[MAXN][20],minsum[MAXN][20];//表示从第i个数起连续2^j个数中的最大值/最小值
void RMQ(int num){
    for(int j=1;j<20;j++)
        for(int i=1;i<=num;i++){
            if(i+(1<<j)-1 <= num)
            {
                maxsum[i][j]=Max(maxsum[i][j-1],maxsum[i+(1<<(j-1))][j-1]);
                minsum[i][j]=Min(minsum[i][j-1],minsum[i+(1<<(j-1))][j-1]);
            }
        }
}

int main()
{
    int i,j,num,t,query;
    while(scanf("%d%d",&num,&query) != EOF)
    {
        for(i=1;i<=num;i++)
        {
            scanf("%d",&maxsum[i][0]);
            minsum[i][0]=maxsum[i][0];
        }
        RMQ(num);
        int st,en,maxl,minl;
        while(query--)
        {
            scanf("%d%d",&st,&en);
            int k=(int)((log(en-st+1))/log(2.0));
            maxl=Max(maxsum[st][k],maxsum[en-(1<<k)+1][k]);
            minl=Min(minsum[st][k],minsum[en-(1<<k)+1][k]);
            printf("%d\n",maxl-minl);
        }
    }
    return 0;
}