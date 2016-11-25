#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stack"
#define maxn 100
typedef char vtype;
typedef struct Anode
{
    int tail,head;
    struct Anode*hlink,*tlink;
}arcnode;
typedef struct Vnode
{
    vtype data;
    arcnode *fin,*fout;
}vexnode;
vexnode G[maxn];
int m;
void createorlist(vexnode G[maxn])
{
    int i,j = 0,k;
    arcnode *p;
    vtype ch,u,v;
    i = m = 0;
    printf("Please input nodes:");
    ch = getchar();
    while(ch!='#')
    {
        m++;
        G[i].data = ch;
        G[i].fin = G[i].fout = NULL;
        i++;
        ch = getchar();
    }
    getchar();
    printf("Please input roads:");
    scanf("%c %c",&u,&v);
    getchar();
    while(u!='#')
    {
        for(k = 0; k < m; k++){
            if(G[k].data==u){i = k;break;}
        }
        for(int k = 0; k < m; k++){
            if(G[k].data==v){j = k;break;}
        }
        p = (arcnode*)malloc(sizeof(arcnode));
        p->tail = i;
        p->head = j;
        p->hlink = G[j].fin;
        G[j].fin = p;
        p->tlink = G[i].fout;
        G[i].fout = p;
        scanf("%c %c",&u,&v);
        getchar();
    }
}

void Creatid(vexnode G2[maxn],int n,int id[maxn])
{
    int count,i;
    arcnode *p;
    for(i = 0; i < n; i++)
    {
        count = 0;
        p = G2[i].fin;
        while(p)
        {
            count ++;
            p = p->hlink;
        }
        id[i] = count;
    }
}

void Topsort(vexnode G1[maxn],int n)
{
    std::stack <int> s;
    int i,j,k,count,id[maxn];
    arcnode *p;
    Creatid(G1,n,id);
    while(!s.empty()) s.pop();
    for(i = 0; i < n; i++)
        if(id[i]==0)
            s.push(i);
    count = 0;
    while(!s.empty())
    {
        j = s.top();
        s.pop();
        printf("%d %c\n",j,G1[j].data);
        count++;
        p = G1[j].fout;
        while(p)
        {
            k = p->head;
            id[k]--;
            if(id[k]==0)
                s.push(k);
            p = p->tlink;
        }
    }
    if(count == n)
        printf("This graph has not cycle\n");
    else
        printf("This graph has cycle\n");
}

int main()
{   int a;
    do{
        createorlist(G);
        Topsort(G,m);
        printf("是否继续：1/0");
        scanf("%d",&a);
    }while(a==1);
}
