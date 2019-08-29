#include "pch.h"
#include <iostream>
#include <queue>
#include <string>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
const int N = 3300;
int graph[N];
typedef struct Vet0
{
	int d_in, d_out;//��¼�ö������Ⱥͳ���
}Vertex;

Vertex vertex[N];

void Get_vertexs(int amount_vet)
{
	for (int i = 0; i < amount_vet; i++)
	{
		vertex[i].d_in = 0;
		vertex[i].d_out = 0;
	}
	return;
}
void Get_sides(int n)
{
	int tmp = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &tmp);//����������һ��Ҫ��scanf��cin�����س�ʱ
			if (tmp)
			{
				vertex[i].d_out++;
				vertex[j].d_in++;
			}
		}
	return;
}

int main()
{
	int n = 0;//�������
	cin >> n;
	Get_vertexs(n);
	Get_sides(n);
	for (int i = 0; i < n; i++)
	{
		cout << vertex[i].d_out << " " << vertex[i].d_in << endl;
	}
	return 0;
}