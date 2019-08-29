/*
程序输入一个字符串（只包含小写字母），请按照字符的输入顺序
建立平衡二叉排序树，并分别输出二叉树的先序序列、中序序列和
后序序列，最后输出该二叉树向左旋转 90 度后的结构


输入：agxnzyimk

输出：
Preorder: xigamknzy
Inorder: agikmnxyz
Postorder: agknmiyzx
Tree:
	z
		y
x
			n
		m
			k
	i
		g
			a
*/
//#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
//#define max(x,y) (x>y?x:y)
using namespace std;
struct AVLNode;
typedef struct AVLNode *AVLTree;
typedef struct AVLNode *Position;
struct AVLNode {
	char element;
	AVLTree lchild;
	AVLTree rchild;
	int height;
};
//*
int max(int x, int y)
{
	return x > y ? x : y;
}
//*/
int Height(AVLTree tree)
{
	if (tree == NULL)
		return -1;
	/*
	tree->height = max(Height(tree->lchild), Height(tree->rchild)) + 1;
	return tree->height;
	//*/
	return tree->height;
}
Position LL_Roate(Position k2)
{
	Position k1 = k2->lchild;
	k2->lchild = k1->rchild;
	k1->rchild = k2;
	k2->height = max(Height(k2->lchild), Height(k2->lchild)) + 1;
	k1->height = max(Height(k1->lchild), k2->height) + 1;
	//k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
	return k1;
}
Position RR_Roate(Position k1)
{
	Position k2 = k1->rchild;
	k1->rchild = k2->lchild;
	k2->lchild = k1;
	k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
	k2->height = max(Height(k2->rchild), k1->height) + 1;
	//k2->height = max(Height(k2->lchild), Height(k2->rchild)) + 1;
	return k2;
}
Position LR_Roate(Position k3)
{
	Position k1 = k3->lchild;
	Position k2 = k1->rchild;
	k3->lchild = k2->rchild;
	k1->rchild = k2->lchild;
	k2->lchild = k1;
	k2->rchild = k3;
	k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
	k3->height = max(Height(k3->lchild), Height(k3->rchild)) + 1;
	k2->height = max(k1->height, k3->height) + 1;
	//k2->height = max(Height(k2->lchild), Height(k2->rchild)) + 1;
	return k2;
}
Position RL_Roate(Position k1)
{
	Position k3 = k1->rchild;
	Position k2 = k3->lchild;
	k1->rchild = k2->lchild;
	k3->lchild = k2->rchild;
	k2->lchild = k1;
	k2->rchild = k3;
	k3->height = max(Height(k3->lchild), Height(k3->rchild)) + 1;
	k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
	k2->height = max(k1->height, k3->height) + 1;
	//k2->height = max(Height(k2->lchild), Height(k2->rchild)) + 1;
	return k2;
}
AVLTree Insert(AVLTree tree, char input)
{
	if (tree == NULL)
	{
		tree = new struct AVLNode;
		tree->element = input;
		tree->height = 0;
		tree->lchild = NULL;
		tree->rchild = NULL;
	}
	else
	{
		if (input < tree->element)
		{
			tree->lchild = Insert(tree->lchild, input);
			if (Height(tree->lchild) - Height(tree->rchild) == 2)
			{
				if (input < tree->lchild->element)
					tree = LL_Roate(tree);
				else
					tree = LR_Roate(tree);
			}
		}
		else
		{
			tree->rchild = Insert(tree->rchild, input);
			if (Height(tree->rchild) - Height(tree->lchild) == 2)
			{
				if (input > tree->rchild->element)
					tree = RR_Roate(tree);
				else
					tree = RL_Roate(tree);
			}
		}
	}
	tree->height = max(Height(tree->lchild), Height(tree->rchild)) + 1;
	return tree;
}
//*
void PreOrder(AVLTree tree) //先序遍历tree，并打印
{

	if (tree == NULL)
		return;
	//*
	cout << tree->element;
	PreOrder(tree->lchild);
	PreOrder(tree->rchild);
	//*/
	return;
}
void InOrder(AVLTree tree) //中序遍历tree，并打印
{
	if (tree == NULL)
		return;
	if (tree->lchild)
	{
		InOrder(tree->lchild);
	}
	cout << tree->element;
	if (tree->rchild)
	{
		InOrder(tree->rchild);
	}
	return;
}
void PostOrder(AVLTree tree) //后序遍历tree，并打印
{
	if (tree == NULL)
		return;
	if (tree->lchild)
	{
		PostOrder(tree->lchild);
	}
	if (tree->rchild)
	{
		PostOrder(tree->rchild);
	}
	cout << tree->element;
	return;
}
void PrintOrder(AVLTree tree)
{
	cout << "Preorder: ";
	PreOrder(tree);
	cout << "\n";
	cout << "Inorder: ";
	InOrder(tree);
	cout << "\n";
	cout << "Postorder: ";
	PostOrder(tree);
	cout << "\n";
	return;
}
void Print(AVLTree tree, int height)
{
	if (tree == NULL)
		return;
	if (tree->rchild)
	{
		tree->rchild->height = tree->height - 1;
		Print(tree->rchild, height);
	}
	for (int i = 4 * (height - tree->height); i > 0; i--)
	{
		cout << " ";
	}
	cout << tree->element << endl;
	if (tree->lchild)
	{
		tree->lchild->height = tree->height - 1;
		Print(tree->lchild, height);
	}
	return;
}
void PrintTree(AVLTree tree)
{
	cout << "Tree:\n";
	if (tree != NULL)
		Print(tree, tree->height);
	return;
}

int main()
{
	AVLTree tree = NULL;
	string s;
	cin >> s;
	for (int i = 0; i < (int)s.length(); i++)
		tree = Insert(tree, s[i]);
	PrintOrder(tree);
	PrintTree(tree);
	return 0;
}