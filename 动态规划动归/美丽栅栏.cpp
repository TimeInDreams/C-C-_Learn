/**************************************
美丽栅栏：http://poj.org/problem?id=1037
题解：https://www.coursera.org/lecture/suanfa-jichu/mei-li-zha-lan-cUU04
动归基础：http://www.cppblog.com/menjitianya/archive/2015/10/23/212084.html
这道题目很难。涉及到两个方面的内容第一是递归，第二是计数
自己在pad上面也有笔记注意看一看
关于动归：经验:当选取的状态，难以进行递推时(分解出的子问题和原
问题形式不一样，或不具有无后效性)，考虑将状态增加限制
条件后分类细化，即增加维度，然后在新的状态上尝试递推
***************************************/
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cstring>
#include <climits>
#include <limits.h>
using namespace std;
typedef long long ll;
const int MAXN = 25;
const int DOWN = 0;
const int UP = 1;
ll c[MAXN][MAXN][2];
void Init()
{
	c[1][1][UP] = c[1][1][DOWN] = 1;
	for (int i = 2; i < MAXN; i++)
	{
		for (int k = 1; k <= i; k++)
		{
			for (int N = 1; N <= k - 1; N++)
				c[i][k][DOWN] += c[i - 1][N][UP];
			for (int N = k; N < i; N++)
				c[i][k][UP] += c[i - 1][N][DOWN];
		}
	}
}
void Print(ll n, ll cc)
{
	int seq[MAXN];//记录第i个位置应当放置长度为几的木棒
	bool used[MAXN];//记录长度为i的木棒是否被用过
	for (int i = 0; i < MAXN; i++)
	{
		seq[i] = 0;
		used[i] = false;
	}
	for (int i = 1; i <= n; i++)//从第一个位置尝试到第n个位置
	{
		ll skipped = 0;//记录已经尝试过的方案
		int NO = 0;//记录长度k在剩余的木棒中是第几个位置
		int k = 0;
		for (k = 1; k <= n; k++)//从长度为1开始测试
		{
			if (used[k]) continue;
			NO++;
			skipped = 0;
			if (i == 1)//由于放置的是第一个，因此无论放哪一个都是合法的
				skipped = c[n][NO][UP] + c[n][NO][DOWN];
			else
			{
				if (k > seq[i-1] && (i <= 2 || seq[i-2] > seq[i-1]))
				{
					skipped = c[n - i + 1][NO][DOWN];//这里的方案数是指从当前位置开始计算
				}
				else if (k < seq[i - 1] && (i <= 2 || seq[i - 2] < seq[i - 1]))
				{
					skipped = c[n - i + 1][NO][UP];
				}
			}
			if (skipped >= cc) break;
			else
				cc -= skipped;
		}
		used[k] = true;
		seq[i] = k;
	}
	for (int i = 1; i < n; i++)
	{
		cout << seq[i] << " ";
	}
	cout << seq[n] << endl;
}
int main()
{
	int T;//总共有T组测试
	cin >> T;
	Init();
	while (T--)
	{
		ll n, cc;
		cin >> n >> cc;
		Print(n, cc);
	}
	return 0;
}