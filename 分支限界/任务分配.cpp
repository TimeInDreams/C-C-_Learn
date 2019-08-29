/*
只有一组测试用例。 输入：第一行是操作员的人数n(4=<n<=13)，接下来的n行里每行有n个数，
分别表示第i名操作员完成第i项任务的时间。 输出：完成所有任务的最短时间。
4
3 8 4 12
9 12 13 5
8 7 9 3
12 7 6 8
*/
#include <iostream>
using namespace std;
int p[15][15];//记录工人i完成任务j需要多长时间
int best_answer = 0, cbest = 0;

void SWAP(int i, int j, int N)
{
    //交换第i列和第j列
	for (int h = 0; h <= N; h++)
	{
		swap(p[h][i], p[h][j]);
	}
}

void PRINT(int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j= 0; j < N; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//求第i列中的最小值
int MIN_Column(int i, int N)
{
	int result = p[0][i];
	for (int j = 1; j < N; j++)
		result = result < p[j][i] ? result : p[j][i];
	return result;
}

void Search(int t, int N)
{
    //如果cbest + 剩余最小值 >= best_answer则没有必要继续进行
	int min_best = 0;
	for (int i = 0; i < N - t; i++)
	{
		min_best += p[N][i];
	}
	if (cbest + min_best >= best_answer) return;


	if (t == N)
	{
		best_answer = best_answer < cbest ? best_answer : cbest;
		return;
	}
	
	for (int i = 0; i < N - t; i++)
	{
		cbest += p[t][i];
		SWAP(i, N - t - 1, N);
		//PRINT(N);
		Search(t + 1, N);

		SWAP(N - t - 1, i, N);
		cbest -= p[t][i];
	}
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> p[i][j];
		best_answer += p[i][i];
	}

    //第n行保存对应列的最小值
	for (int i = 0; i < n; i++)
	{
		p[n][i] = MIN_Column(i, n);
	}

	Search(0, n);
	cout << best_answer << endl;
	return 0;
}