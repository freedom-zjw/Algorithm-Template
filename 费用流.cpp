//最小费用流

struct edge{
    int x,y,f,c,nxt;
}e[E];
int en,head[N],pre[N],dist[N],visited[N];

void add(int x,int y,int f,int c){
    e[en].x=x;
    e[en].y=y;
    e[en].f=f;
    e[en].c=c;
    e[en].nxt=head[x];
    head[x]=en++;
}

void addedge(int x,int y,int f,int c){
    add(x,y,f,c);
    add(y,x,0,-c);
}

bool spfa(int s,int t,int n){
    int i,v,cur;
    queue<int> q;
    for(i=0;i<n;i++){
        pre[i]=-1;
        visited[i]=false;
        dist[i]=inf;
    }
    visited[s]=true;
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        cur=q.front();
        q.pop();
        visited[cur]=false;
        for(i=head[cur];i!=-1;i=e[i].nxt)
            if(e[i].f){
                v=e[i].y;
                if(dist[v]>dist[cur]+e[i].c){
                    dist[v]=dist[cur]+e[i].c;
                    pre[v]=i;
                    if(!visited[v]){
                        visited[v]=true;
                        q.push(v);
                    }
                }
            }
    }
    return dist[t]!=inf;
}

int cost(int s,int t,int n){
    int i,flow=inf,ans=0;
    while(spfa(s,t,n)){
        ans+=dist[t];
        for(i=pre[t];i!=-1;i=pre[e[i].x])
            flow=min(flow,e[i].f);
        for(i=pre[t];i!=-1;i=pre[e[i].x]){
            e[i].f-=flow;
            e[i^1].f+=flow;
        }
    }
    return ans;
}
