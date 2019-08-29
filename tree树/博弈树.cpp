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
	int score;//�����ڲ������м�¼�÷�
	int height;//���ڼ�¼���ߣ��ڲ������У���������˲��ܱ�Ӯ�������Ҫ�ҵ�һ����ߵķ�֧��
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
void Print_Tree(TREE tree, int depth) //���������ӡ���ṹ
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
		if (depth % 2 == 1)//��������player��turn
		{
			tree->score = -depth;//player��·���ߣ�cpӮ
		}
		else//ż������cp��turn
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
				//���Ǽٶ����е�˫������Ѱ�����Ž⣬��ô����player��turn���ԣ�ѡ��cp������С��·��
				tree->score = min(tree->score, p->score);
				p = p->sibling;
			}
		}
		else
		{
			while (p)
			{
				//����cp���ԣ�Ӧ��ѡ��ʹ���Լ���������·��
				tree->score = max(tree->score, p->score);
				p = p->sibling;
			}
		}
	}
	return;
}
void Cp_think(POSITION tree, int depth)
{
	//�����һ����ͨ��depth����żȷ����˭��turn
	//���У�ż��ʱcp��turn
	//��һ���棬����ȷ�������ڵ��cp����
	//depthԽС������Խ��
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
	if (tree->score == -INF)//�����ڲ���˫����������ѡ��ʱ��cpһ�����䣬��ʱcp����ѡ��·������
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
	else if (tree->score != tree->child->score)//��cp�л���һ��Ӯ��ʱ��ѡ�����������Ǹ�����ʱҲ��·����̵�
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
		cout << "player:\n";//��ʾplayer��������
		cin >> tmp;
		POSITION root = tree;
		tree = IsIllegal(tree, tmp);//�ж��û��Ƿ��������ͬʱ���½ڵ㣬������һ��
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
		tree = IsIllegal(tree, tmp);//�����ǶԽڵ���и��£���Ϊ��������һ��
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
	int flag = 0;//flag���ڱ�־˭����
	cin >> flag;
	if (flag)//player����
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
	Calculate_Tree_Height(tree);//Ϊ����Ĳ�����׼��
	Play(tree);
	return 0;
}