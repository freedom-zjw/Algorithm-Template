/*
草地上有些树，用树做篱笆围一块最大的面积来养牛，每头牛要50平方米才能养活，问最多能养多少只羊
凸包求面积，分解成三角形用叉积求面积。
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node 
{
    int x,y;
}list[10001],sta[10001];
int n,top; 
int  multi(node p1,node p2,node p0)  
{
    int x1,y1,x2,y2;
    x1= p1.x-p0.x;
    y1= p1.y-p0.y;
    x2= p2.x-p0.x;
    y2= p2.y-p0.y;

    return  x1*y2 - x2*y1; 
}
double dis(node p1,node p2) 
{
    return sqrt(  double((p1.x-p2.x)*(p1.x-p2.x))  +  double((p1.y-p2.y)*(p1.y-p2.y))  );
}

int cmp(node p1,node p2) 
{

    int  tt= multi(p1,p2,list[1]);
    if( tt>0) return 1;
    if (  tt==0  && dis(p1,list[1])<dis(p2,list[1]) ) return 1;
    return 0;
}
void qs(int l ,int r) 
{
    if (l>=r) return ;
    int i=l,j=r;
    node no= list[(l+r)/2];
    do{
        while( cmp(list[i],no) )i++;
        while( cmp(no,list[j]) )j--;
        if(i<=j)
        {
            node tt=list[i]; list[i]=list[j]; list[j]=tt;
            i++;j--;
        }
    }while(i<=j);
    qs(i,r);
    qs(l,j);
}
void tubao()
{

    qs(2,n); 
    int i;
    for(i=1;i<=2;i++)  sta[i]= list[i];
    top=2;
    for(i=3;i<=n;i++)
    {
        while(top>1 && multi(sta[top],list[i],sta[top-1])<=0) top--;
        sta[++top]=list[i];
    }
}
int main()
{   long long t;
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&list[i].x,&list[i].y);
        if( list[i].y<list[1].y || (list[i].y==list[1].y && list[i].x<list[1].x) )
        {
           node ttt=list[1]; list[1]=list[i]; list[i]= ttt;
        }
    }
    tubao();
    t=0;
    for (i=2;i<top;i++)t+=multi(sta[i],sta[i+1],sta[1]);
    if (t<0)t=-t;t/=2;
    printf("%I64d\n",t/50);
    return 0;
}