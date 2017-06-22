#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;
#define rep(i,u,v) for (int i=(u);i<=(v);i++)
#define sqr(x) (x)*(x)
const double Pi = 3.1415926536 , Eps = 1e-8 , Ini = 50 , Dec = 0.80;
const int N=60,Times = 20;
struct node{
	double x,y;
}a[N],b[N];
double m[N];
int n;
double distant(node n0,node n1)
{ return sqr(n0.x-n1.x)+sqr(n0.y-n1.y);}
node rotate(node O,node P,double beta)
{   node ret=O;
    P.x-=O.x;P.y-=O.y;
    ret.x+=P.x*cos(beta)-P.y*sin(beta);
    ret.y+=P.y*cos(beta)+P.x*sin(beta);
    return ret;
}
double caln(node n0)
{   b[1]=n0;
    rep(i,1,n)
       b[i+1]=rotate(a[i],b[i],m[i]);
    return distant(b[1],b[n+1]);
}
void solve()
{   srand(1996-04-22);
    node p0;p0.x=p0.y=0;
    double d;
    d=caln(p0);
    for (double E=Ini;E>Eps;E*=Dec)
        rep(t,1,Times)
        {     node p1;
              p1.x=p0.x+E*(rand()%10001-5000);
              p1.y=p0.y+E*(rand()%10001-5000);
              double dd=caln(p1);
              if (dd<d){
              	    d=dd;p0=p1;
              }
        }
    caln(p0);
    rep(i,1,n)
        printf("%.0lf %.0lf\n",floor(b[i].x+0.5),floor(b[i].y+0.5));
}
int main()
{    scanf("%d",&n);
     rep(i,1,n)scanf("%lf%lf",&a[i].x,&a[i].y);
     rep(i,1,n){
     	  scanf("%lf",&m[i]);
     	  m[i]=m[i]*Pi/180.0;
     }
     solve();
}