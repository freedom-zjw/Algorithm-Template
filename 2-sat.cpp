#include<cstdio>  
#include<cstring>  
#include<iostream>
using namespace std;  
const int N = 2010;  
struct node{  
    int x,y,next;  
}edge[1000010],edge2[1000010];  
int n,len,len2,tot,vis_num,cnt,top,topo[N],ru[N];
int first[N],sta[2010],low[N],dfn[N],belong[N];  
bool instack[N];  
// instack是判断点i在不在栈中
//dfn[i]表示节点搜索的次序编号
//low[i]为或i的子树能够追溯到的最早的栈中节点的次序号 
// belong[i]表示属于什么连通分量，cnt为分量总数
void addedge(int a,int b){  
    edge[len].x=a; edge[len].y=b;  
    edge[len].next=first[a]; first[a]=len++;  
}  
void addedge2(int a,int b){  
    edge2[len2].x=a; edge2[len2].y=b;  
    edge2[len2].next=first[a]; first[a]=len2++;  
} 
void getmap()  
{  
    int m,a,b,c,d;  
    scanf("%d",&m);  
    len=0;  
    memset(first,-1,sizeof(first));  
    while(m--){  
        scanf("%d%d%d%d",&a,&b,&c,&d);  
        addedge(2*a+c,2*b+(1-d));  
        addedge(2*b+d,2*a+(1-c));  
    }  
}  
void tarjan(int x){  
    int i;  
    dfn[x]=low[x]=++vis_num;  //为节点x设定次序编号和 low 初值 
    instack[x]=true;   
    sta[++top]=x;//将x压入栈中
    for(i=first[x];i!=-1;i=edge[i].next){  //枚举x的每一条边
        int u=edge[i].y;  
        if(dfn[u]==-1){  //如果节点x未被访问过 
            tarjan(u);   //继续向下找
            if(low[x]>low[u])low[x]=low[u];// 更新节点x所能到达的最小次数层
        }  
        else if(instack[u] && low[x]>dfn[u])//如果节点u在栈内
		         low[x]=dfn[u];  
    }  
    if(low[x]==dfn[x]){  //如果节点x是强连通分量的根 
        cnt++;  //连通分量标号加1
        do{  
            i=sta[top];  
            top--;         
            instack[i]=false;  //将i退栈
            belong[i]=cnt;  //出栈节点属于第cnt个强连通分量 
        } while(i!=x);//ֱ直接将x从栈中退出
    }  
}   
int pairs[N],col[N];   
bool bo[N];     
bool solve(){  
    int i;  
    vis_num=cnt=top=0;  //初始化次序计数器，连通分量标号，栈顶指针为0 
    memset(instack,false,sizeof(instack));  
    memset(belong,-1,sizeof(belong));  
    memset(dfn,-1,sizeof(dfn));//结点搜索的次序编号数组为0，同时可以当是否访问的数组使用
    memset(low,0,sizeof(low));  
    for(i=0;i<2*n;i++){   //枚举每个结点，搜索连通分量 
        if(dfn[i]==-1)tarjan(i);   ///i未被访问 则找i结点的连通分量
    }  
    int flag=1;  
    for(i=0;i<n;i++){  
        if(belong[2*i]==belong[2*i+1]){//若同一组的两个数据在一个连通分量中就矛盾，2-SAT无解 
            return false; 
        }  
        pairs[belong[2*i]]=belong[2*i+1];//否则把两个数据作为一对数
        pairs[belong[2*i+1]]=belong[2*i];  
    }  
    return true;
}   
void topsort()
{   int i,head=1,tail=0;
    memset(col,-1,sizeof(col));
    for (i=1;i<=cnt;i++)
      if (!ru[i])topo[++tail]=i;
    while (head<=tail)
    {  
         int x=topo[head];head++;
         if (col[x]==-1)
         {  col[x]=1;
            col[pairs[x]]=0;
         }
         for (i=first[x];i!=-1;i=edge2[i].next)
         {   int y=edge2[i].y;
             if (--ru[y]==0)topo[++tail]=y;
         }
    }
}
void build_regraph()
{   len2=0;
    memset(first,-1,sizeof(first));
    memset(ru,0,sizeof(ru));
    for (int i=0;i<len;i++)
     if (belong[edge[i].x]!=belong[edge[i].y]){//不是同一个强连通分量的就加反向边 
          addedge2(belong[edge[i].y],belong[edge[i].x]);
           ru[belong[edge[i].x]]++;
     }
}
void print()
{ 
    for (int i=0;i<n;i++)
    {  
         if (i!=0)printf(" ");
         if (col[belong[i*2]]==1)printf("0");
         else printf("1");
    }
    printf("\n");
}
int main()  
{   freopen("a.in","r",stdin);
    while(scanf("%d",&n)!=EOF)  
    {   getmap();   //构图
        if(!solve())printf("NO\n");//2-sat
        else {
        	printf("YES\n");
            build_regraph();//缩点，建逆图
            topsort();//对新图拓扑排序
            print();//输出解
        }
    }  
}