/*
题目大意：将给出的火星字符串翻译成英文字符串，每个单词有对应的英文单词，如果不存在对应的就输出原有的即可。
解题思路：对火星字符串进行建树，在最后一个字母上存下对应的英文字符串。这里要注意一个标记，不然会超内存。
 */
#include<iostream>
using namespace std;
int tot=0;
struct node
{
    int c[27],times;
    char st[11];
    void init()
    {   memset(c,0,sizeof(c));
        times=0;
    }
}t[510001];
void insert(char *s1,char *s2)
{    int p=0;
    while(*s2)
    {
        int index=*s2-'a'+1;
        if (t[p].c[index]==0)
        {   t[p].c[index]=++tot;
			t[tot].init();           
        }
        p=t[p].c[index];
        s2++;
    }
    t[p].times++;
    strcpy(t[p].st,s1);
}
char* search(char *s)
{    int p=0,i;
    for (i=0;s[i];i++)
    {
        int index=s[i]-'a'+1;
        if (t[p].c[index]==0)return s;
        p=t[p].c[index];
    }
    if (t[p].times==1)return t[p].st;
    else return s;
}
int main()
{   int i,j,k,num,len;
    char s1[25],s2[25],s[3005];
    scanf("%s",s1);
    t[0].init();
    while(scanf("%s",s1)!=EOF)
    {
        if (strcmp(s1,"END")==0)break;
        scanf("%s",s2);
        insert(s1,s2);
    }
    scanf("%s",s1);getchar();
    while(1)
    {
        gets(s);
        if (strcmp(s,"END")==0)break;
        len=strlen(s);num=0;
        for (i=0;i<len;i++)
        {
            if (s[i]>='a'&&s[i]<='z')
            s1[num++]=s[i];
            else
            { 
                 s1[num]=0;num=0;
                 printf("%s",search(s1));
                 printf("%c",s[i]);
            }
        }
        printf("\n");
    }
}