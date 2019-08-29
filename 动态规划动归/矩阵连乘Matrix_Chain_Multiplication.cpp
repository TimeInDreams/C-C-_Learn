//https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
//矩阵A1,A2,...,An
//对应行和列为p0,p1,p2,...p[n-1]
//result[i][j] == result[(i - 1) * i / 2 + j - 1]//这里下标以矩阵为标准
//result[n][n] == result[(n-1)*n/2+n-1] == result[n*(n+1)/2-1]
const int N = 110;
int p[N], result[N][N], s[N][N];

inline int Min(int a, int b)
{
	return a < b ? a : b;
}
inline int Cal_A(int i, int k, int j)
{
	return result[i][k] + result[k + 1][j] + p[i - 1] * p[k] * p[j];
}

string BackTrack(int l, int r)
{
	if (s[l][r] == 0)//不再进行划分
	{
		if (l == r)//仅有一个
		{
			return string("A") + to_string(l);
		}
		else
		{
			return string("(A") + to_string(l) + string("A") + to_string(r) + string(")");
		}
	}
	else
		return string("(") + BackTrack(l, s[l][r]) + BackTrack(s[l][r] + 1, r) + string(")");
}

int MatrixChainOrder(int n)
{
	for (int k = 1; k < n; k++)
	{
		for (int i = 1; i + k <= n; i++)
		{
			int tmp;
			int j = i + k;
			tmp = Cal_A(i, i, j);
			s[i][j] = i;
			for (int h = i + 1; h < j; h++)
			{
				int t = Cal_A(i, h, j);
				if (tmp > t)
				{
					tmp = t;
					s[i][j] = h;
				}
			}
			result[i][j] = tmp;
		}
	}
	return result[1][n];
}

void Matrix_Chain_Multiplication(int *p, int n)
{
	//result[n][n] == result[(n-1)*n/2+n-1] == result[n*(n+1)/2-1]
	memset(result, 0, sizeof(result));
	memset(result, 0, sizeof(s));
	int out = MatrixChainOrder(n - 1);//n-1个矩阵
	cout << out << endl;
	string s = BackTrack(1, n - 1);
	if (n - 1 == 1)
	{
		cout << "(" + s + ")" << endl;
	}
	else
		cout << BackTrack(1, n - 1) << endl;//n-1个矩阵
}

int main()
{
	//int K;
	//cin >> K;
	//while (K--)
	//{
	//关于n的具体取值见题意，看清楚n是矩阵个数还是矩阵个数+1
	int n;
	cin >> n;
	for (int i = 0; i < n + 1; i++)
		cin >> p[i];
	Matrix_Chain_Multiplication(p, n + 1);
	//}
	return 0;
}