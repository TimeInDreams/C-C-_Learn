/*
编写程序实现二叉树的如下操作：
1) 建立二叉链表
2) 二叉树的先序、中序、后序遍历
3) 求解二叉树的叶子结点个数
4) 将二叉树中所有结点的左、右子树相互交换
输入：
　　扩展二叉树先序序列：ab#d##ce###。其中#代表空指针。

输出：
　　二叉树的凹入表示
　　二叉树的先序序列、中序序列、后序序列
　　二叉树叶子结点个数
　　左、右子树相互交换后的二叉树的凹入表示
　　左、右子树相互交换后的二叉树的先序序列、中序序列、后序序列。
*/
/*
思路：
这道题的结构分为：
    1.建立二叉树
    2.先序遍历，中序遍历，后序遍历
    3.左右子树的交换
    4.树的输出
    5.求解二叉树叶子节点
函数功能包括：
    1.建立二叉树
        难点在于数据的分析，可以将数据放入char数组中，从下标为1开始
        这道题目的数据是只记录存在的节点及其子节点
    2.遍历
        先序：
            根节点，左孩子，右孩子
        中序：
            左孩子，根节点，右孩子
        后序：
            左孩子，右孩子，根节点
    3.左右子树的交换
        判断是否有孩子，有孩子就交换，从上往下递归进行
    4.树的输出
        先序遍历输出
    5.求解二叉树叶子节点
        凡是没有孩子节点的都是叶子节点
        判断是否有孩子，如果没有孩子就是叶子节点，返回1
        如果有孩子，就对孩子进行递归
*/
#include <iostream>
#include <cstring>
using namespace std;
typedef struct node *POSITION, *BiTree;
struct node
{
    char element;
    POSITION Lchild, Rchild;
};
BiTree Initial() //创建一棵树的节点
{
    BiTree tree = new struct node;
    tree->Lchild = NULL;
    tree->Rchild = NULL;
    return tree;
}
BiTree Create(BiTree tree) //依据数据在根节点tree上建树
{
    /*
    当前元素的下一个就是自己的左孩子，若没有左孩子则下下个就是他的右孩子；
    如果有孩子，就在对应的孩子处以此为根节点进行建树
    */
    char c = getchar();
    if (c == '#' || c == '\n')
    {
        return NULL;
    }
    else
    {
        tree = Initial();
        tree->element = c;
        tree->Lchild = Create(tree->Lchild);
        tree->Rchild = Create(tree->Rchild);
    }
    return tree;
}
void PrintTree_BITree(BiTree tree, int depth)
{
    if (tree == NULL) //如果是NULL则返回
        return;
    for (int i = 0; i < 4*depth; i++)
    {
        cout << " ";
    }
    cout << tree->element << endl;
    PrintTree_BITree(tree->Lchild, depth + 1);
    PrintTree_BITree(tree->Rchild, depth + 1);
    return;
}
void PrintTree(BiTree tree) //先序打印tree的结构
{
    /*
    在实际操作过程中我们需要知道处于树的哪一层，但是用户不希望输入过多参数；
    所以我们再次写一个函数，使得具有depth参数
    */
    PrintTree_BITree(tree, 0);
    return;
}
void PreOrder(BiTree tree) //先序遍历tree，并打印
{
    /*
    先序：
            根节点，左孩子，右孩子
    */
    if (tree == NULL)
        return;
    cout << tree->element;
    PreOrder(tree->Lchild);
    PreOrder(tree->Rchild);
    return;
}
void InOrder(BiTree tree) //中序遍历tree，并打印
{
    /*
    中序：
            左孩子，根节点，右孩子
    */
    if (tree->Lchild)
    {
        InOrder(tree->Lchild);
    }
    cout << tree->element;
    if (tree->Rchild)
    {
        InOrder(tree->Rchild);
    }
    return;
}
void PostOrder(BiTree tree) //后序遍历tree，并打印
{
    /*
    后序：
        左孩子，右孩子，根节点
    */
    if (tree->Lchild)
    {
        PostOrder(tree->Lchild);
    }
    if (tree->Rchild)
    {
        PostOrder(tree->Rchild);
    }
    cout << tree->element;
    return;
}
int NumberLeaf(BiTree tree) //计算tree的叶子的数目并打印
{
    if (tree == NULL)
        return 0;
    if (tree->Lchild == NULL && tree->Rchild == NULL)
        return 1;
    else
        return NumberLeaf(tree->Lchild) + NumberLeaf(tree->Rchild);
}
void TreeSwap(BiTree tree) //对treeo中的所有左右孩子进行交换，并将交换后的树根节点返回
{
    if(tree == NULL)
        return;
    BiTree tmp = tree->Lchild;
    tree->Lchild = tree->Rchild;
    tree->Rchild = tmp;
    TreeSwap(tree->Lchild);
    TreeSwap(tree->Rchild);
    return;
}
void PrintOrder(BiTree tree)
{
    cout << "pre_sequence  : ";
    PreOrder(tree);
    cout << "\n";
    cout << "in_sequence   : ";
    InOrder(tree);
    cout << "\n";
    cout << "post_sequence : ";
    PostOrder(tree);
    cout << "\n";
    return;
}
int main()
{
    BiTree tree;
    tree = Create(tree);
    cout << "BiTree\n";
    PrintTree(tree);
    PrintOrder(tree);
    //*
    int number_of_leaf = NumberLeaf(tree);
    cout << "Number of leaf: " << number_of_leaf << endl;
    TreeSwap(tree);
    cout << "BiTree swapped\n";
    PrintTree(tree);
    PrintOrder(tree);
    //*/
    return 0;
}