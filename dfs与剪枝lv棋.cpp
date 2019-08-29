/*
https://acm.bitnp.net/problem/9

�ڼ�ѵ���зǳ�����һ��lv�壬�������������һ��n��m������˫����Ϊ�������ͷ��ط���

���ط�������������������������ӣ��������������Ⱥ�˳�򣬰��º�λ�ò��ܸı䣩��
��������Ҫѡ��һ��·�������(0,0)�ߵ��յ�(0,1)��ÿ��ֻ����ֻ���ϡ��¡����ҷ����ƶ�����ֻ���ƶ�һ����λ��
����������ÿһ������һ���ҽ�һ�Σ������γԵ��������ط���������ߵ��յ�������һ�Ρ���������

ǿ���ɭ�����ڴ����������Ϸ��ɭ��ڷ���������Ӻ�ǿ��˵��A�ˡ�ɭ��Ϊ��cha��ǿ������Ҫ���������Լ����

�����������ӱ���������·����1/4,2/4,3/4���ֱ�Ե������������ӡ������·�����Ȳ���4�ı�������ȡ����

ǿ����A�ˣ���������������ģ������������ô����������һ��һ���ж����ַ�������ɶ�ɭ��ġ���������
Input

����������������������ÿ����������ĵ�һ�а�����������n��m(2��n,m��8)���ֱ��ʾ���̵ĳ����������һ����6������
x_1,y_1
x_2,y_2
x_3,y_3,
0��xn, 0��y��m��
Output

�����(0,0)(0,0)������������·����1/4,2/4,3/4���������˳��Ե�������������ߵ�(0,1)(0,1)�ķ�������
*/
//#include "pch.h"
#include <iostream>
#include <stack>
#include <string.h>
using namespace std;
typedef pair<int, int> P;
const int GUARD_NUM = 3;
int x[GUARD_NUM], y[GUARD_NUM], stp[GUARD_NUM];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int n = 0, m = 0;//�ֱ�Ϊx��y��
int x_source = 0, y_source = 0;
int x_finish = 0, y_finish = 1;
int ways_num = 0;
bool visit[9][9];
int guard_dead_num = 0;

int Compare_ints(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}
bool isFinish(P p, int step)
{
	if (guard_dead_num == 3)
		if (p.first == x_finish && p.second == y_finish)
		{
			int tmp[GUARD_NUM];
			for (int i = 0; i < GUARD_NUM; ++i)
			{
				tmp[i] = stp[i];
			}
			qsort(tmp, GUARD_NUM, sizeof(int), Compare_ints);
			if (tmp[0] == step / 4 && tmp[1] == step / 2 && tmp[2] == step * GUARD_NUM / 4)
				ways_num++;
			return 1;
		}
	return 0;
}
int isGuard(P p, int step)
{
	for (int i = 0; i < GUARD_NUM; ++i)
	{
		if (p.first == x[i] && p.second == y[i])
		{
			if (guard_dead_num == 0 && step > n * m / 4)
				return -2;
			if (guard_dead_num == 1 && step > n * m / 2)
				return -2;
			if (guard_dead_num == 2 && step > n * m * 3 / 4)
				return -2;
			guard_dead_num++;
			stp[i] = step;
			return i;
		}
	}
	return -1;
}

void dfs(stack<P> &s, int step)
{
	P p = s.top();
	s.pop();
	if (visit[p.first][p.second])
		return;
	int flag = isGuard(p, step);
	//��֦��step�ܳ����ᳬ��n*m
	if (flag == -2)
		return;
	if (isFinish(p, step))
		return;

	visit[p.first][p.second] = true;
	for (int i = 0; i < 4; ++i)
	{
		int x_tmp = p.first + dx[i];
		int y_tmp = p.second + dy[i];
		if (x_tmp >= 0 && x_tmp < n && y_tmp >= 0 && y_tmp < m)//���ܳ���ͼ�α߽�
		{
			if (!visit[x_tmp][y_tmp])
			{
				P tmp(x_tmp, y_tmp);
				s.push(tmp);
				dfs(s, step + 1);
			}
		}
	}
	visit[p.first][p.second] = false;
	if (flag > -1)
	{
		guard_dead_num--;
		stp[flag] = 0;
	}
	return;
}
int main()
{
	int k = 0;
	while (~scanf("%d%d", &n, &m))//m��y�ᣬn��x��
	{
		if (n == 0 && m == 0)
			break;
		k++;
		for (int i = 0; i < GUARD_NUM; ++i)
			scanf("%d%d", &x[i], &y[i]);
		ways_num = 0;//����������·������
		guard_dead_num = 0;//������guard������
		memset(visit, 0, sizeof visit);
		memset(stp, 0, sizeof stp);
		stack<P> s;
		while (!s.empty())
		{
			s.pop();
		}
		P p(x_source, y_source);
		s.push(p);
		dfs(s, 1);
		printf("Case %d: %d\n", k, ways_num);
	}
	return 0;
}
