/*
��ʵ��ʵ���ڽӱ��ʾ������ͼ�Ĺ�����ȱ����������������ͼ�Ķ������кͱ�����
(����������*Ϊ������־, �������� - 1, -1Ϊ������־)��
��������Ϊͼ���ڽӱ�͹�����ȱ������С����磺

��������Ϊ��
a
b
c
d
e
f
*
0, 1
0, 4
1, 4
1, 5
2, 3
2, 5
3, 5
- 1, -1

��������Ϊ��
the ALGraph is
a 4 1
b 5 4 0
c 5 3
d 5 2
e 1 0
f 3 2 1
the Breadth - First - Seacrh list : aebfdc

�����ĿӦ��ע��ͼ����ͨ�����
*/
#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
const int N = 1e2;

typedef struct node {
	char vet;
	bool known;/*���ڼ���vertex�Ƿ񱻷��ʹ�*/
}Vertex;
struct Adj_vet
{
	int vet_num;
	struct Adj_vet* next;
};
struct Vet_head {
	char vet_head;
	int vet_num;
	struct Adj_vet* adj_vet;/*���ڴ���ÿ�����head�������ڵĶ����lst*/
};

struct Vet_head vet_head[N];
Vertex vertex[N];
void Enque(Vet_head head, int vet)
{
	Adj_vet *p = head.adj_vet;
	while (p)
	{
		if (p->next)
		{
			if (vet <= p->next->vet_num)
				p = p->next;
			else {
				break;
			}
		}
		else break;
	}
	Adj_vet* tmp = p->next;
	p->next = new Adj_vet;
	p->next->vet_num = vet;
	p->next->next = tmp;
	return;
}

void Bfs(int vet_num)
{
	if (vertex[vet_num].known)
		return;
	queue<Adj_vet*>que;
	cout << vertex[vet_num].vet;
	vertex[vet_num].known = 1;
	Adj_vet* p = vet_head[0].adj_vet;
	que.push(p);
	while (!que.empty())
	{
		p = que.front();
		que.pop();
		while (p->next)
		{
			int vet_num = p->next->vet_num;
			if (!vertex[vet_num].known)
			{
				que.push(vet_head[vet_num].adj_vet);
				cout << vertex[vet_num].vet;
				vertex[vet_num].known = 1;
			}
			p = p->next;
		}
	}
	return;
}
void bfs(int amount_vet)
{
	for (int i = 0; i < amount_vet; i++)
		Bfs(i);//����ͼ����ͨʱ���еĽڵ�û�з��ʣ�������Ҫ��ÿһ����������ж�
	return;
}

int main()
{
	int amount_vet = 0;//��¼���������
	for (int i = 0; i < N; i++)
	{
		amount_vet = i;
		char tmp = 0;
		cin >> tmp;
		if (tmp == '*')
			break;
		vertex[i].vet = tmp;
		vertex[i].known = 0;
		vet_head[i].vet_head = tmp;
		vet_head[i].vet_num = i;
		vet_head[i].adj_vet = new Adj_vet;
		vet_head[i].adj_vet->next = NULL;
	}
	while (true)
	{
		int a = 0, b = 0;
		fscanf_s(stdin, "%d%*c%d", &a, &b);
		if (a == -1)
			break;
		if (a < amount_vet && b < amount_vet)
		{
			Enque(vet_head[a], b);
			Enque(vet_head[b], a);
		}
	}


	cout << "the ALGraph is\n";
	for (int i = 0; i < amount_vet; i++)
	{
		cout << vet_head[i].vet_head;
		Adj_vet* p = vet_head[i].adj_vet;
		while (p->next)
		{
			cout << " " << p->next->vet_num;
			p = p->next;
		}
		cout << endl;
	}
	cout << "the Breadth-First-Seacrh list:";
	bfs(amount_vet);
	cout << endl;
	return 0;
}