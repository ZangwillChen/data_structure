#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 20
typedef struct Bsnode
{
    char data[M];
    struct Bsnode *Lchild,*Rchild;
}BSN,*BSP;

typedef struct node
{
    BSP bsp;
    struct node* next;
}snode,*slink;
///////////////////////////////
int Emptystack(slink S)  //栈空判断
{
    if(S==NULL)return(1);
    else return(0);
}
///////////////////////////////
BSP Pop(slink* top)//出栈
{
    BSP bsp2;
    slink p;
    if(Emptystack(*top))return NULL;
    else
    {
        bsp2=(*top)->bsp;
        p=*top;*top=(*top)->next;
        free(p);return(bsp2);
    }
}
////////////////////////////////
void Push(slink* top,BSP bsp)//进栈
{
    slink p=NULL;
    p=(slink)malloc(sizeof(snode));
    p->bsp=bsp;
    p->next=*top;
    *top=p;
}
//////////////////////////////
void Clearstack(slink* top)//置栈空
{	slink p;
    while(*top!=NULL)
    {
        p=(*top)->next;
        Pop(top);
        *top=p;
    }
    *top=NULL;
}
////////////////////////////
BSP Getstop(slink S)//取栈顶元素
{
    if(S!=NULL)return(S->bsp);
    return NULL;
}

///////////////////////////
BSP BSTinsert(BSP T,BSP S)   //插入S
{
    BSP q, p;
    if(T==NULL)
        return(S);            //树为空时,以S为根
    p=T;
    q=NULL;                   //q为p的父节点
    while(p)
    {
        q=p;
        if(strcmp(S->data,p->data)==0)//S已存在,返回
        {
            free(S);
            return(T);
        };
        if(strcmp(S->data,p->data)<0)
            p=p->Lchild;
        else
            p=p->Rchild;
    }
    if(strcmp(S->data,q->data)<0)
        q->Lchild=S;
    else
        q->Rchild=S;
    return(T);
}

//////////////////////////////
BSP createBst()    //创建二叉排序树
{
    BSP T,S;
    char key[M];
    T=NULL;
    printf("请输入一句英文!(以 .结束)\n");
    scanf("%s",&key);
    while(strcmp(key,"."))
    {
        S=(BSP)malloc(sizeof(BSN));
        strcpy(S->data,key);
        S->Lchild=S->Rchild=NULL;
        T=BSTinsert(T,S);
        scanf("%s",&key);
    }
    return(T);
}
//////////////////////////////////
int Inorder(BSP T)   ///////中序遍历非递归
{
    BSP p=T;
    slink S=NULL;
    printf("LDR遍历输出:\n");
    Push(&S,T);
    while(!Emptystack(S))
    {
        while((p=Getstop(S))&&p)
            Push(&S,p->Lchild);
        p=Pop(&S);
        if(!Emptystack(S))
        {	
            p=Pop(&S);              	
            printf("%s ",p->data);            
            Push(&S,p->Rchild);          
        }
    }
    return 0;
}  
////////////主函数
int main()
{
    int a;
    do{
    BSP tree;
    tree=createBst();
    Inorder(tree);
    printf("\n");
    printf("是否继续?是:1否:0\n");
    scanf("%d",&a);
    }while(a);
}
