#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 101010
typedef struct node
{
    char element;
    struct node *next;
} NODE;
NODE *sta1;
NODE *Create(NODE *);     //创建栈
void Clean(NODE *);       //清除栈
NODE *FindLast(NODE *);   //找到栈顶位置
void Push(NODE *, char);  //入栈
bool Judge(NODE *, char); //判断运算符入栈方式，直到为真时入栈sta1
char Pop(NODE *);         //返回栈顶元素,不删除
void Delete(NODE *);      //删除栈顶元素
void Out(NODE *);         //输出最终结果
bool IsEmpty(NODE *);     //判断栈是否为空
int main()
{
    int n = 0; //共有n个表达式
    scanf("%d", &n);
    char s[N];

    sta1 = Create(sta1); //存储运算符
    //sta2 = Create(sta2); //存储操作数
    while (n--)
    {
        scanf("%s", &s);
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == '#')
            {
                Out(sta1);
                Clean(sta1);
            }
            else
            {
                Push(sta1, s[i]);
            }
        }
    }
    return 0;
}
void Out(NODE *p1)
{
    char s[N];
    p1 = p1->next;
    int i = 0;
    while (p1)
    {
        s[i++] = p1->element;
        p1 = p1->next;
    }
    while (i)
    {
        printf("%c", s[--i]);
    }
    printf("\n");
    return;
}
NODE *FindLast(NODE *p)
{
    while (p->next)
        p = p->next;
    return p;
}
bool IsEmpty(NODE *p)
{
    if (p->next == NULL)
        return 1;
    else
        return 0;
}
void Delete(NODE *p)
{
    if (IsEmpty(p))
        return;
    while (p->next->next)
    {
        p = p->next;
    }
    NODE *tmp = p->next;
    free(tmp);
    p->next = NULL;
    return;
}
char Pop(NODE *p)
{
    p = FindLast(p);
    return p->element;
}
NODE *Create(NODE *head)
{
    head = (NODE *)malloc(sizeof(NODE));
    head->element = 0;
    head->next = NULL;
    return head;
}
void Clean(NODE *head)
{
    NODE *tmp = head;
    head = head->next;
    tmp->next = NULL;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return;
}
void Push(NODE *sta1, char input)
{
    //运算符复杂入栈
    if (input == '+' || input == '*' || input == '/' || input == '-' || input == '^' || input == '(' || input == ')')
    {
        //栈为空,或者栈顶元素为左括号“（”,或者优先级比栈顶元素高，直接进栈
        //否则，将sta1栈顶运算符弹出压入sta2，重复上述
        while (!Judge(sta1, input))
        {
            printf("%c", Pop(sta1));
            Delete(sta1);
        }
        if (input != ')')
        {
            NODE *p1 = FindLast(sta1);
            p1->next = (NODE *)malloc(sizeof(NODE));
            p1->next->element = input;
            p1->next->next = NULL;
        }
        else
        {
            Delete(sta1);
        }
    }
    //操作数简单入栈
    else
    {
        printf("%c", input);
    }
    return;
}

bool Judge(NODE *p, char input)
{
    if (p->next == NULL)
        return 1;
    p = FindLast(p);
    if (p->element == '(' || input == '(' || input == '^')
        return 1;
    if (input == '-' || input == '+')
    {
        if (p->element == '-' || p->element == '+' || p->element == '*' || p->element == '/' || p->element == '^')
            return 0;
        else
            return 1;
    }
    if (input == '*' || input == '/')
    {
        if (p->element == '*' || p->element == '/' || p->element == '^')
            return 0;
        else
            return 1;
    }
    if (input == ')')
    {
        if (p->element == '(')
            return 1;
        else
            return 0;
    }
}