/*
给出二叉树的中序遍历序列和后序遍历序列，编程还原该二叉树。

输入：
　　第1行为二叉树的中序遍历序列
　　第2行为二叉树的后序遍历序列

输出：
　　二叉树的按层遍历序列

例如：
输入：
badcfeg
bdfgeca
输出：
abcdefg
*/
/*
思路：
这道题目相对简单，注意一下中序和后序遍历特点即可。
前序遍历：根左右
中序遍历：左根右
后序遍历：左右根


以输入的例子为例：
中序遍历：badcfeg
后序遍历：bdfgeca
根据后序遍历可知a是根节点，依据前序，a前面的是左子树，a后面的是右子树
将其分为：b，a，dcfeg和b，dfgec，a这样我们将其分为三部分，输出根节点即可
这时，对左子树和右子树进行递归处理即可

1.根据post序列找到根节点（就是最后一个元素）
2.根据根节点找到in序列中的位置
3.根据位置划分左右子树
4.根据左子树的最后一个元素和右子树的第一个元素对post进行划分
5.根据4中的划分对左右子树从1循环开始
*/
#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <stdio.h>
using namespace std;
const int N = 1e2;
typedef struct node *POSITION, *TREE;
struct node
{
    char element;
    POSITION lchild, rchild;
};
void PRINT(char *, char *);
void Divide(char *, char *);
char *Get()
{
    char *ch = new char[N];
    for (int i = 0; i < N; i++)
    {
        char tmp = getchar();
        if (tmp == '\n')
        {
            ch[i] = '\0';
            return ch;
        }
        ch[i] = tmp;
    }
}
int Find(char *ch, char target)
{
    //找到target在char数组中的位置
    int i = 0;
    int len = (int)strlen(ch);
    for (i = 0; i < len && ch[i] != target; i++)
        ;
    return i;
}
//从index开始从from复制length长的字符串到to当中
char *Copy(char *from, char *to, int index, int length)
{
    if (length == 0)
        return NULL;
    to = new char[length + 1];
    to[length] = 0;
    for (int i = 0; i < length; i++)
    {
        to[i] = from[i + index];
    }
    return to;
}
TREE Build(char *in, char *post, TREE tree)
{
    if (post == NULL)
        return NULL;
    int root_index = Find(in, post[(int)strlen(post) - 1]); //在中序中找到root节点位置
    int left_length = root_index;                      //左子树序列的长度
    int right_length = (int)strlen(in) - root_index - 1;    //右子树序列的长度
    char *left_tree_in = NULL;
    char *right_tree_in = NULL;
    char *left_tree_post = NULL;
    char *right_tree_post = NULL;
    left_tree_in = Copy(in, left_tree_in, 0, left_length);
    right_tree_in = Copy(in, right_tree_in, root_index + 1, right_length);
    left_tree_post = Copy(post, left_tree_post, 0, left_length);
    right_tree_post = Copy(post, right_tree_post, left_length, right_length);
    char root_c = in[root_index];
    delete in;
    delete post;
    if (root_c == '\0')
        return NULL;
    else
    {
        tree = new struct node;
        tree->element = root_c;
        tree->lchild = Build(left_tree_in, left_tree_post, tree->lchild);
        tree->rchild = Build(right_tree_in, right_tree_post, tree->rchild);
    }
    return tree;
}
// 二叉树的分层打印
void Print(TREE tree)
{
    if (tree == NULL)
        return;
    queue<POSITION> q;
        q.push(tree);
    int curLevelNum; // 当前层的节点数
    while (q.size())
    {
        TREE tmp = q.front();
        q.pop();
        cout << tmp->element;
        if (tmp->lchild)
            q.push(tmp->lchild);
        if (tmp->rchild)
            q.push(tmp->rchild);
    }
    cout << "\n";
}
int main()
{
    char *in = Get();
    char *post = Get();
    TREE tree = NULL;
    tree = Build(in, post, tree);
    Print(tree);
    return 0;
}