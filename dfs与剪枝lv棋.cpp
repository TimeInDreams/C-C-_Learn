/*
https://acm.bitnp.net/problem/9

在集训队中非常流行一种lv棋，这种棋的棋盘是一个n×m的网格，双方分为进攻方和防守方。

防守方在棋盘上三个点摆下三个棋子（这三个棋子有先后顺序，摆下后位置不能改变），
进攻方需要选择一条路径从起点(0,0)走到终点(0,1)，每次只能向只能上、下、左、右方向移动，且只能移动一个单位。
进攻方经过每一个格子一次且仅一次，且依次吃掉三个防守方棋子最后走到终点才算完成一次“进攻”。

强神和森神现在打算玩这个游戏，森神摆放完防守棋子后，强神说我A了。森神为了cha掉强神于是要加入另外的约束：

进攻方的棋子必须在整个路径的1/4,2/4,3/4处分别吃掉三个防守棋子。（如果路径长度不是4的倍数则下取整）

强神又A了，他觉得这个很无聊，所以现在想让聪明的你计算一共一下有多少种方法来完成对森神的“进攻”。
Input

输入包含若干组测试用例，每组测试用例的第一行包含两个整数n和m(2≤n,m≤8)，分别表示棋盘的长与宽，接下来一行有6个整数
x_1,y_1
x_2,y_2
x_3,y_3,
0≤xn, 0≤y≤m。
Output

输出从(0,0)(0,0)出发，在整个路径的1/4,2/4,3/4处按输入的顺序吃掉三个棋子最后走到(0,1)(0,1)的方法数。
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
int n = 0, m = 0;//分别为x，y轴
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
	//剪枝，step总长不会超过n*m
	if (flag == -2)
		return;
	if (isFinish(p, step))
		return;

	visit[p.first][p.second] = true;
	for (int i = 0; i < 4; ++i)
	{
		int x_tmp = p.first + dx[i];
		int y_tmp = p.second + dy[i];
		if (x_tmp >= 0 && x_tmp < n && y_tmp >= 0 && y_tmp < m)//不能超过图形边界
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
	while (~scanf("%d%d", &n, &m))//m是y轴，n是x轴
	{
		if (n == 0 && m == 0)
			break;
		k++;
		for (int i = 0; i < GUARD_NUM; ++i)
			scanf("%d%d", &x[i], &y[i]);
		ways_num = 0;//符合条件的路径数量
		guard_dead_num = 0;//死亡的guard的数量
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
