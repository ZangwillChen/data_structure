#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef int datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}Qnode,*Qlink;
typedef struct
{
    Qnode *front,*rear;
}linkqueue;
void Lcreatequeue(linkqueue *q)
{
    q->front=(Qlink)malloc(sizeof(Qnode));
    q->front->next=NULL;
    q->rear=q->front;
}
void Clearqueue(linkqueue *q)
{
    q->front=q->rear=0;
}
int Lemptyqueue(linkqueue *q)
{
    if (q->front==q->rear) return (1);
    else return (0);
}
void Lenqueue(linkqueue *q,datatype e)
{
    Qlink p;
    p=(Qlink)malloc(sizeof(Qnode));
    p->data=e;
    p->next=NULL;
    q->rear->next=p;q->rear=p;
}
datatype Ldequeue(linkqueue *q)
{
    Qlink p;
    if (Lemptyqueue(q)) return NULL;
    else{
        p=q->front;
        q->front=p->next;
        free(p);
        return (q->front->data);
    }
}
void main()
{
    char a,b;int c = 0;
    linkqueue q;
    Lcreatequeue(&q);
    do {
        a=getchar();
        switch (a) {
            case ' ':break;c=1;
            case '0':
            {if (Lemptyqueue(&q)) {
                    printf("队列为空\n");
                printf("请继续输入\n");c=1;
                }
                else {
                    b=Ldequeue(&q);
                    printf("%c已出队\n",b);
                    printf("请继续输入\n");
                }
            }break;
            case '@':{
                if (Lemptyqueue(&q)) {
                    printf("队列为空\n");return;}
                else
                {
                    printf("所有元素出队：\n");
                    while (Lemptyqueue(&q)!=1) {
                        b=Ldequeue(&q);
                        printf("%c",b);
                    }
                    printf("\n");
                    return;
                }
            }break;
            case '\n':break;
            default :{Lenqueue(&q,a);c=1;}break;
        }
    } while (c);
}