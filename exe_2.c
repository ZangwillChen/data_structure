#include<stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char data;
    struct node *next;
}snode,*slink;
typedef struct node1
{
    int data;
    struct node1 *next;
}snode1,*slink1;
int Emptystack(slink S)     //检测栈空
{
    if(S==NULL)
        return (1);
    else return (0);
}
char Pop(slink*top)         //出栈
{
    char e;
    slink p;
    if(Emptystack(*top))
        return (-1);
    else
    {
        e=(*top)->data;
        p=*top;*top=(*top)->next;
        free(p);return (e);
    }
}
void Push(slink*top,char e)     //进栈
{
    slink p;
    p=(slink)malloc(sizeof(snode));
    p->data=e;
    p->next=*top;
    *top=p;
}
void Clearstack(slink*top)      //置空栈
{
    slink p;
    while (*top!=NULL)
    {
        p=(*top)->next;
        Pop(top);
        *top=p;
    }
    *top=NULL;
}
char Getstop(slink S)//取栈顶
{
    if (S!=NULL)
        return (S->data);
    return (0);
}
int Emptystack1(slink S)     //检测栈空
{
    if(S==NULL)
        return (1);
    else return (0);
}
char Pop1(slink1*top)         //出栈
{
    char e;
    slink1 p;
    if(Emptystack1(*top))
        return (-1);
    else
    {
        e=(*top)->data;
        p=*top;*top=(*top)->next;
        free(p);return (e);
    }
}
void Push1(slink1*top,char e)     //进栈
{
    slink1 p;
    p=(slink1)malloc(sizeof(snode1));
    p->data=e;
    p->next=*top;
    *top=p;
}
void Clearstack1(slink1*top)      //置空栈
{
    slink1 p;
    while (*top!=NULL)
    {
        p=(*top)->next;
        Pop1(top);
        *top=p;
    }
    *top=NULL;
}
char Getstop1(slink1 S)//取栈顶
{
    if (S!=NULL)
        return (S->data);
    return (0);
}
/***********************/
/*****符号优先级比较***/
/**********************/
int Precede(char x,char y)
{   int a = 0,b = 0;
    switch (x){
        case '(':a=0;break;
        case '+':
        case '-':a=1;break;
        case '*':
        case '/':a=2;break;
    }
    switch (y) {
        case '+':
        case '-':b=1;break;
        case '*':
        case '/':b=2;break;
        case '(':b=3;break;
    }
    if (a>=b)
        return (1);
    else return (0);
}
/********************/
/*******中后序转换****/
/*******************/
void mid_post(char post[],char mid[])
{
    
    int i=0,j=0;
    char x; int a;
    slink S=NULL; //置空栈
    Clearstack(&S);
    Push(&S,'#'); //结束符入栈
    do
    {
    x=mid[i++]; //扫描当前表达式分量x
    switch(x)
    {
        case ' ':break;
        case '#':
        {
            while(!Emptystack(S))
            {   post[j++]=' ';
                post[j++]=Pop(&S);} //栈非空时
        }break;
        case ')':
        {
            while(Getstop(S)!='(')
            {
                post[j++]=' ';
                post[j++]=Pop(&S);//反复出栈直到遇到'(' Pop(&s);
            } Pop(&S);//退掉'('
        }break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        {
            while(Precede(Getstop(S),x)) //栈顶运算符（Q1）与x比较
            {
                post[j++]=' ';
            post[j++]=Pop(&S);
        }
            Push(&S,x); //Q1<x时，x进栈
            post[j++]=' ';
        }break;
        default:post[j++]=x;}
    }while(x!='#');
    post[j]='\0';
    Clearstack(&S);
}
            /******************/
/**后缀表达式求值**/
/******************/
int postcount(char post[])
{
    int i=0,h;
    float a1=0,a2,g=0,g1;
    char x;
    float z = 0.0,a,b;
    slink1 S=NULL;
    while (post[i]!=0) {
        x=post[i];
        switch (x) {
            case ' ':break;
            case '+':b=Pop1(&S);a=Pop1(&S);z=a+b;Push1(&S, z);break;
            case '-':b=Pop1(&S);a=Pop1(&S);z=a-b;Push1(&S, z);break;
            case '*':b=Pop1(&S);a=Pop1(&S);z=a*b;Push1(&S, z);break;
            case '/':b=Pop1(&S);a=Pop1(&S);z=a/b;Push1(&S, z);break;
            default:
            {
                g=0;g1=0;a1=0;a2=0;h=0;
                while(post[i]!=' ')
                {
                    if(post[i]!='.')
                    {
                        g1=post[i]-'0';
                        g = g*10 + g1;
                        i++;
                    }
                    else
                    {
                        h=i;
                        i++;
                        while(post[i]!=' ')
                        {
                            a2=post[i]-'0';
                            for(int c=0;c<i-h;c++)
                            {
                                a2 = a2*(0.1);
                            }
                            a1 = a1 + a2;
                            i++;
                        }
                    };
                }
                g = g+a1;
                Push1(&S,g);
            }

        }
        i++;
    }
    if (!Emptystack1(S)){  return (z);
        Clearstack1(&S);}
    else return (-1);
}
int PD(char B[])
{
    int i=0,c,j = 0,k;
    c=strlen(B);
    while (B[i]!='#') {
        
        switch(B[i])
        {
            case ' ':break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                j=j+1;
                if(B[j]==' ')
                {
                    while(B[j]==' ') j++; switch(B[j])
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                        printf("1非法输入!请重新输入!\n");return(0);break; }
                }
            }break;
            case '+':
            case '-':
            case '*':
            case '/':
            {
                j=i-1;
                while(B[j]==' ') j--;
                switch(B[j])
                {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '(':
                    case '#':printf("2非法输入!请重新输入!\n");return(0);break; }
                k=i+1;
                while(B[k]==' ') k++;
                switch(B[k])
                {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case ')':
                    case '#':printf("3非法输入!请重新输入!\n");return(0);break; }
            }break;
            case '(':
            {
                j=i-1;
                while(B[j]==' ') j--;
                switch(B[j])
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '#':
                    case ')':printf("4非法输入!请重新输入!\n");return(0);break; }
                k=i+1;
                while(B[k]==' ') k++;
                switch(B[k])
                {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '#':printf("5非法输入!请重新输入!\n");return(0);break; }
            }break;
            case ')':
            {
                j=i-1;
                while(B[j]==' ') j--;
                switch(B[j])
                {
                    case '(':printf("6非法输入!请重新输入!\n");return(0);break; }
                k=i+1;
                while(B[k]==' ') k++;
                switch(B[k])
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':printf("7非法输入!请重新输入!\n");return(0);break; }
            }break;
            case '\0':break;
            default:printf("8非法输入!请重新输入!\n");return(0);
        }
        i++;
    }
    if(B[0]=='#')
    {
        printf("表达式为空!请重新输入!\n");return(0); }
    else if (B[c-1]!='#')
    {
        printf("9非法输入!请重新输入!\n");return(0);
    }
    else return(1);
}
int main()
{
    char A[100],B[100];
    float a,b,c;
    do{
        do
        {
            printf("请输入中缀表达式:\n");
            B[100]=fflush(stdin);
            gets(B);
            while(B[0]=='\0')
            {
                B[100]=fflush(stdin);
                gets(B);
            }
            b=PD(B);
        }while(b==0);
    mid_post(A, B);
    printf("后缀表达式为：\n");
    printf("%s\n",A);
    a=postcount(A);
    printf("结果=%f\n",a);
    printf("是否继续输入？是：1，否：0\n");
    scanf("%f",&c);
    }while(c==1);
}