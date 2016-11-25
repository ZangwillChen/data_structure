#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef struct node
{
    int d;
    struct node *next;
}Linknode,*Link;
Link Createlist()                       //创建链表
{
    int a;char ch;int i=0;
    Link H,P,r;
    H=(Link)malloc(sizeof(Linknode));
    r=H;
    while (scanf("%d",&a))
    {
        P=(Link)malloc(sizeof(Linknode));
        P->d=a;r->next=P;
        r=P;
        ch=getchar();
        i++;
        if ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) {       //判断输入是否含字母，如果含字母则结束程序
            printf("输入错误\n");
            exit(0);
            return 0;
        }
    }
    r->next=NULL;
    return(H);
}
Link Adjmax(Link H,int k)               //判断相邻k个节点的和为最大值的节点
{
    Link p,q,r;
    int m0,m1,m2;int s=1;int i;int j=k;
    m0=0;m1=0;m2=0;
    p=H;
    while ((p->next!=NULL)) {
        p=p->next;
        j--;
    }
    if (j>0) {
        printf("输入错误\n");
        exit(0);
        return 0;
    }
    if (p==NULL)
        return (p);
    if(q==NULL)
        return(p);
    p=H->next;
    q=H->next;
   
    q=q->next;
    for(i=0;i<k;i++)
    {
        m0+=p->d;
        p=p->next;
    }
    m2=m0;r=p;i=2;
    while (r->next!=NULL) {                        //取下一相邻节点的指针
        m1=m2-q->d;
        m1=m1+p->d;
        if (m1>m0) {
            m0=m1;
            s=i;
        }
        m2=m1;
        r=p;
        p=p->next;
        q=q->next;
        i++;
    }
    int m=s-1;
    p=H->next;
    for (m; m>0; m--) {
        p=p->next;
    }
    printf("最大节点为：%d,",p->d);
    return (s);
}
int main()
{
    int c,d;
    Link k,l,b,p,q;
    do
    {
    printf("请输入k的值：\n");
    scanf("%d",&d);
    if (d<=1) {                         //判断k的值是否正确
        printf("k输入错误\n");
        return 0;
        }
    printf("请输入(#为结束符):\n");
    p=k=Createlist();
    l=Adjmax(k,d);
    printf("序号为：%d\n",l);
    while (p->next) {                   //清空链表
        q=p;
        p=p->next;
        free(q);
    }
    free(p);
    printf("是否输入下一组整数：是：1，否：0\n");
    getchar();
    scanf("%d",&b);}
    while(b);
}