/*
输入：
(a,(b),(c,(d),(e,(g),(h)),(f)))
输出：
a
    b
    c
        d
        e
            g
            h
        f
Number of nodes of degree 0: 5
Number of nodes of degree 1: 0
Number of nodes of degree 2: 2
Number of nodes of degree 3: 1
*/
/*
思路：
这道题的难点在于如何解析输入，将其转化为树结构。
函数分为以下部分：
    1.建树
    2.输出树
    3.输出对应度数的节点个数
1.建树：
    将数据存入一个queue中，采用first in first out 的操作
    碰到'('就向下建一级，碰到')'就向上返回一级
    返回值为指针
    采用递归操作
2.输出树
    按照类似于binary tree的先序遍历的格式进行输出
    先打印根节点
    从左向右向下递归孩子节点
3.输出对应度数节点的个数
    首先找到degree of the tree(maximum degrees of nodes)
    找到从0到degree of tree的节点数目


    degree of tree:
        找每个节点的孩子数目，degree_of_tree = max{degree_of_node}
*/
#include <iostream>
#include <cstring>
#define max(x, y) x > y ? x : y
using namespace std;
typedef struct node *POSITION, *TREE;
struct node
{
    char element;
    POSITION child, sibling;
};
TREE CreateTree(TREE tree)
{
    char c = getchar();
    while (c == ',')
        c = getchar();
    if (c == ')' || c == '\n')
        return NULL;
    else
    {
        if (c == '(')
        {
            if (tree == NULL)
                tree = CreateTree(tree);
            if (tree && tree->child == NULL)
                tree->child = CreateTree(tree->child);
            if (tree && tree->child)
            {
                POSITION tmp = tree->child;
                if (tmp->sibling == NULL)
                    tmp->sibling = CreateTree(tmp->sibling);
                while (tmp->sibling)
                {
                    while (tmp->sibling)
                        tmp = tmp->sibling;
                    tmp->sibling = CreateTree(tmp->sibling);
                }
            }
        }
        else
        {
            tree = new struct node;
            tree->element = c;
            tree->child = NULL;
            tree->sibling = NULL;
        }
    }
    return tree;
}
//*
void Print_Tree(TREE tree, int depth) //先序遍历打印树结构
{
    if (tree == NULL)
        return;
    for (int i = 0; i < 4 * depth; i++)
    {
        cout << " ";
    }
    cout << tree->element << endl;
    Print_Tree(tree->child, depth + 1);
    if (tree->child)
    {
        POSITION tmp = tree->child;
        while (tmp)
        {
            Print_Tree(tmp->sibling, depth + 1);
            tmp = tmp->sibling;
        }
    }
    return;
}
void PrintTree(TREE tree)
{
    Print_Tree(tree, 0);
    return;
}
int FindDegreeOfNode(POSITION node)
{
    int degree_of_node = 0;
    if (node->child)
    {
        POSITION tmp = node->child;
        while (tmp->sibling)
        {
            degree_of_node++;
            tmp = tmp->sibling;
        }
        degree_of_node++;
    }
    return degree_of_node;
}
int FindDegreeOfTree(POSITION node)
{
    if (node == NULL)
        return 0;
    int degree_of_siblings = max(FindDegreeOfNode(node), FindDegreeOfTree(node->child));
    while (node->sibling)
    {
        degree_of_siblings = max(degree_of_siblings, FindDegreeOfTree(node->sibling));
        node = node->sibling;
    }
    return degree_of_siblings;
}
void NumberOfNodes(TREE tree, int *num)
{
    if (tree == NULL)
        return;
    num[FindDegreeOfNode(tree)]++;
    if (tree->sibling)
        NumberOfNodes(tree->sibling, num);
    NumberOfNodes(tree->child, num);
    return;
}
void PrintNumberNodesOfDegree(TREE tree)
{
    int degree_of_tree = FindDegreeOfTree(tree);
    int *num = new int[degree_of_tree + 1];
    memset(num, 0, sizeof(int));
    NumberOfNodes(tree, num);
    for (int i = 0; i <= degree_of_tree; i++)
    {
        cout << "Number of nodes of degree " << i << ": " << num[i] << endl;
    }
    return;
}
//*/
int main()
{
    TREE tree = NULL;
    tree = CreateTree(tree);
    //cout << "hhh\n";
    PrintTree(tree);
    //*
    int degree_of_tree = FindDegreeOfTree(tree);
    cout << "Degree of tree: " << degree_of_tree << endl;
    PrintNumberNodesOfDegree(tree);
    //*/
    return 0;
}