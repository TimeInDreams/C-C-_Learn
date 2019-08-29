/*
���룺
(a,(b),(c,(d),(e,(g),(h)),(f)))
�����
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
˼·��
�������ѵ�������ν������룬����ת��Ϊ���ṹ��
������Ϊ���²��֣�
	1.����
	2.�����
	3.�����Ӧ�����Ľڵ����
1.������
	�����ݴ���һ��queue�У�����first in first out �Ĳ���
	����'('�����½�һ��������')'�����Ϸ���һ��
	����ֵΪָ��
	���õݹ����
2.�����
	����������binary tree����������ĸ�ʽ�������
	�ȴ�ӡ���ڵ�
	�����������µݹ麢�ӽڵ�
3.�����Ӧ�����ڵ�ĸ���
	�����ҵ�degree of the tree(maximum degrees of nodes)
	�ҵ���0��degree of tree�Ľڵ���Ŀ


	degree of tree:
		��ÿ���ڵ�ĺ�����Ŀ��degree_of_tree = max{degree_of_node}
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