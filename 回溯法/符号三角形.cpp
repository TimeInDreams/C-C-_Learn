#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
using namespace std;
int half, num_of_ways, num_of_ones;
int p[25][25];
void Search(int t, int N)
{
    //这里需要严格注意的是分支限界的条件是(N+1) * N / 4
	if (num_of_ones > half / 2 || t * (t - 1) / 2 - num_of_ones > half / 2) return;
	if (t > N)
	{
		num_of_ways++;
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		p[1][t] = i;
		num_of_ones += i;
		for (int j = 2; j <= t; j++)
		{
			p[j][t - j + 1] = p[j - 1][t - j + 1] ^ p[j - 1][t - j + 2];
			num_of_ones += p[j][t - j + 1];
		}
		Search(t + 1, N);
		for (int j = 2; j <= t; j++)
		{
			num_of_ones -= p[j][t - j + 1];
		}
		num_of_ones -= i;
	}
}
inline void init(int N)
{
	half = N * (N + 1) / 2;
	num_of_ways = 0;
	num_of_ones = 0;
	//memset(p, 0, sizeof(p));
}
int main()
{
	int N;
	while (cin >> N)
	{
		init(N);
		if (half % 2) cout << "0\n";
		else
		{
			Search(1, N);
			cout << num_of_ways << endl;
		}
	}
	return 0;
}