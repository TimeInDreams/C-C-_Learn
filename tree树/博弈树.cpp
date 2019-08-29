/*
(a,(b,(x)),(c,(d),(e,(g),(h)),(f)))

a

	b

		x

	c

		d

		e

			g

			h

		f

Who play first(0: computer; 1: player )?

1

player:

c

computer: d

Sorry, you lost.

Continue(y/n)?

y

Who play first(0: computer; 1: player )?

1

player:

x

illegal move.

player:

b

computer: x

Sorry, you lost.

Continue(y/n)?

y

Who play first(0: computer; 1: player )?

0

computer: c

player:

f

Congratulate, you win.

Continue(y/n)?

n
*/
#include "pch.h"
#include <iostream>
#include <cstring>
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x > y ? y : x)
using namespace std;
const int INF = 1e5;
typedef struct node *POSITION, *TREE;
struct node
{
	char element;
	int score;//用于在博弈树中记录得分
	int height;//用于记录树高，在博弈树中，如果出现了不能必赢的情况就要找到一个最高的分支树
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


bool Winner(TREE tree)
{
	bool winner = 0;
	if (tree->child == NULL)
		winner = 1;
	return winner;
}
POSITION IsIllegal(POSITION tree, char tmp)
{
	if (tmp == tree->child->element)
		tree = tree->child;
	POSITION p = tree->child;
	if (p)
		while (p->sibling)
		{
			if (tmp == p->sibling->element)
			{
				tree = p->sibling;
				break;
			}
			else
				p = p->sibling;
		}
	return tree;
}
void Calculate_Score(POSITION tree, int depth)
{
	if (tree->child == NULL)
	{
		if (depth % 2 == 1)//奇数层是player的turn
		{
			tree->score = -depth;//player无路可走，cp赢
		}
		else//偶数层是cp的turn
			tree->score = -INF;
	}
	else
	{
		tree->score = tree->child->score;
		POSITION p = tree->child->sibling;
		if (depth % 2)
		{
			while (p)
			{
				//我们假定所有的双方都是寻求最优解，那么对于player的turn而言，选择cp获益最小的路径
				tree->score = min(tree->score, p->score);
				p = p->sibling;
			}
		}
		else
		{
			while (p)
			{
				//对于cp而言，应当选择使得自己获益最大的路径
				tree->score = max(tree->score, p->score);
				p = p->sibling;
			}
		}
	}
	return;
}
void Cp_think(POSITION tree, int depth)
{
	//在这里，一方面通过depth的奇偶确定是谁的turn
	//其中，偶数时cp的turn
	//另一方面，用于确定各个节点的cp收益
	//depth越小，收益越大
	POSITION p = tree->child;
	while (p)
	{
		Cp_think(p, depth + 1);
		p = p->sibling;
	}
	Calculate_Score(tree, depth);
	return;
}
char Think(TREE tree)
{
	Cp_think(tree, 0);
	char tmp = tree->child->element;
	if (tree->score == -INF)//这是在博弈双方进行最优选择时，cp一定会输，这时cp尽量选择路径长的
	{
		POSITION p = tree->child;
		int height = tree->child->height;
		while (p->sibling)
		{
			if (p->height < p->sibling->height)
			{
				tmp = p->sibling->element;
				height = p->sibling->height;
			}
			p = p->sibling;
		}
	}
	else if (tree->score != tree->child->score)//当cp有机会一定赢的时候，选择收益最大的那个，这时也是路径最短的
	{
		POSITION p = tree->child;
		while (p)
		{
			if (tree->score == p->score)
			{
				tmp = p->element;
				break;
			}
			p = p->sibling;
		}
	}
	return tmp;
}
void Playing(TREE tree)
{
	while (true)
	{
		char tmp = 0;
		cout << "player:\n";//提示player进行输入
		cin >> tmp;
		POSITION root = tree;
		tree = IsIllegal(tree, tmp);//判断用户是否输入错误，同时更新节点，向下走一层
		if (tree == root)
		{
			cout << "illegal move.\n";
			continue;
		}
		if (Winner(tree))
		{
			cout << "Congratulate, you win.\n";
			break;
		}
		tmp = Think(tree);
		cout << "computer: " << tmp << endl;
		tree = IsIllegal(tree, tmp);//这里是对节点进行更新，因为向下走了一层
		if (Winner(tree))
		{
			cout << "Sorry, you lost.\n";
			break;
		}
	}
	return;
}

void Play(TREE root)
{
	cout << "Who play first(0: computer; 1: player )?\n";
	//cout << "player:\n";
	int flag = 0;//flag用于标志谁先走
	cin >> flag;
	if (flag)//player先走
	{
		Playing(root);
	}
	else
	{
		char ch = Think(root);
		cout << "computer: " << ch << endl;
		POSITION tmp = IsIllegal(root, ch);
		if (Winner(tmp))
		{
			cout << "Sorry, you lost.\n";
		}
		else
			Playing(tmp);
	}
	cout << "Continue(y/n)?\n";
	char tmp = 0;
	cin >> tmp;
	if (tmp == 'y')
		Play(root);
	return;
}

int Calculate_Tree_Height(TREE tree)
{
	if (tree->child == NULL)
	{
		tree->height = 0;
	}
	else
	{
		tree->height = Calculate_Tree_Height(tree->child);
		POSITION p = tree->child->sibling;
		while (p)
		{
			tree->height = max(tree->height, Calculate_Tree_Height(p));
			p = p->sibling;
		}
		tree->height++;
	}
	return tree->height;
}
int main()
{
	TREE tree = NULL;
	tree = CreateTree(tree);
	PrintTree(tree);
	Calculate_Tree_Height(tree);//为下面的博弈做准备
	Play(tree);
	return 0;
}