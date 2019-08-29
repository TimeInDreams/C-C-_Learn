/*
输入要求：

第一行为活动的个数 N(1<=N<=1 000 000) 。

接下来 N 行为 Si 和 Fi(0<=Si<Fi<=2 000 000 000) ，分别代表第 i 个活动的开始时间和结束时间。活动 i 的区间段为 [Si,Fi)

输出要求：

输出有一行 M ，为所需教室的最小数量。

关于这个题目，我们使用贪心算法进行解决。
我们维护两个数据，一个是result，一个是处于busy状态的教室。
我们将所有的开始时间与结束时间分离，进行贪心计算。
1. 如果开始时间小于结束时间，那么就需要一个新的教室，busy状态的教室加一
2. 如果开始时间等于结束时间，那么busy状态的教室不增不减
3. 如果开始时间大于结束时间，那么busy状态的教室就要减一
这些步骤实际上是以时间为线，但是时间不是递增的，而是根据结束时间变化的，每当一个教室陷入busy状态，
那么就有了一个结束时间，随着时间的演进
*/
#include<algorithm>
#include<cstdio>
#define max(a,b) (a>b?a:b)
using namespace std;
const int MAXN = 1e6 + 5;
int begin_time[MAXN], end_time[MAXN];
int main() 
{
	int N; 
	scanf_s("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf_s("%d%d", begin_time + i, end_time + i);
	}
	sort(begin_time, begin_time + N);
	sort(end_time, end_time + N);
	int sum = 0, res = 0;//sum是处于busy状态的房间数目
	for (int i = 0, j = 0; i < N && j < N;) 
	{
		//i,j交替来模拟时间的推移
		if (begin_time[i] == end_time[j])
			++i, ++j;
		while (begin_time[i] < end_time[j] && i < N)
			++i, ++sum;
		//printf("sum=%d\n",sum);
		res = max(res, sum);
		while (end_time[j] < begin_time[i] && j < N)
			++j, --sum;//因为有的房间活动已经结束，故busy房间数减少
	}
	printf("%d\n", res);

	return 0;
} 