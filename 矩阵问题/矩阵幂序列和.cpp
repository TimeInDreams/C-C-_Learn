#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
ll mod = 1000000007;
typedef ll** MATRIXTYPE;
//int mod;
void PRINT(MATRIXTYPE a, int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column - 1; j++)
		{
			while (a[i][j] < 0)
			{
				a[i][j] += mod;
			}
			//a[i][j] %= MODULE;
			cout << a[i][j] << " ";
		}
		while (a[i][column - 1] < 0)
		{
			a[i][column - 1] += mod;
		}
		cout << a[i][column - 1] << endl;
	}
}
MATRIXTYPE MALLOC(int row, int column)
{
	MATRIXTYPE a = new ll*[row];
	for (int i = 0; i < row; i++)
		a[i] = new ll[column];
	return a;
}
MATRIXTYPE multAB(MATRIXTYPE a, MATRIXTYPE b, int a_row, int a_column, int b_row, int b_column)//矩阵a,b以及结果的row与column的数量
{
	MATRIXTYPE c = MALLOC(a_row, b_column);
	for (int i = 0; i < a_row; i++)
	{
		for (int j = 0; j < b_column; j++)
		{
			ll tmp = 0;
			for (int k = 0; k < a_column; k++)
			{
				tmp += a[i][k] * b[k][j];
				tmp %= mod;
			}
			c[i][j] = tmp % mod;
		}
	}
	//PRINT(c, row, column);
	return c;
}
MATRIXTYPE POWER(ll exponent, MATRIXTYPE a, int row, int column)
{
	//printf("exponent: %d\n", exponent);
	//PRINT(a, row, column);
	if (exponent == 1)
	{
		return a;
	}
	if (exponent % 2 == 0)
	{
		MATRIXTYPE tmp = POWER(exponent / 2, a, row, column);
		//PRINT(tmp, row, column);
		return multAB(tmp, tmp, row, column, row, column);
	}
	else
	{
		MATRIXTYPE tmp = POWER(exponent / 2, a, row, column);
		//PRINT(tmp, row, column);
		return multAB(multAB(tmp, tmp, row, column, row, column), a, row, column, row, column);
	}
}
MATRIXTYPE sumAB(MATRIXTYPE a, MATRIXTYPE b, int row, int column)
{
	//MATRIXTYPE c = MALLOC(row, column);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			b[i][j] += a[i][j];
			if (b[i][j] > mod)
				b[i][j] %= mod;
		}
	return b;
}
MATRIXTYPE solve(int n, ll k, MATRIXTYPE a)
{
	MATRIXTYPE I = MALLOC(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				I[i][j] = 1;
			else
				I[i][j] = 0;

	MATRIXTYPE ans = MALLOC(2 * n, 2 * n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans[i][j] = a[i][j];
	for (int i = 0; i < n; i++)
		for (int j = n; j < 2 * n; j++)
			if (i + n == j)
				ans[i][j] = 1;
			else
				ans[i][j] = 0;
	for (int i = n; i < 2 * n; i++)
		for (int j = 0; j < n; j++)
			ans[i][j] = 0;
	for (int i = n; i < 2 * n; i++)
		for (int j = n; j < 2 * n; j++)
			if (i == j)
				ans[i][j] = 1;
			else
				ans[i][j] = 0;
	//PRINT(ans, 2 * n, 2 * n);
	ans = POWER(k, ans, 2 * n, 2 * n);
	//PRINT(ans, 2 * n, 2 * n);
	MATRIXTYPE b = MALLOC(n, n);
	for (int i = 0; i < n; i++)
		for (int j = n; j < 2 * n; j++)
			b[i][j - n] = ans[i][j];
	//minusAB(I, a, n, n);

	return multAB(a, b, n, n, n, n);;
}

int main()
{
	int n, k;
	cin >> n >> k >> MODULE;
	MATRIXTYPE a = MALLOC(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	a = solve(n, k, a);
	PRINT(a, n, n);
	return 0;
}
