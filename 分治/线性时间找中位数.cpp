/*
主油管道为东西向，确定主油管道的南北位置，使南北向油井喷油管道和最小。要求线性时间完成。

1<= 油井数量 <=2 000 000

输入要求：

输入有油井数量行，第 K 行为第 K 油井的坐标 X ,Y 。其中， 0<=X<2^31,0<=Y<2^31 。

输出要求：

输出有一行， N 为主管道最优位置的最小值

问题就是线性时间求y坐标的中位数
*/
//#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;
const int MOUNT = 2000000; //油井数量
const int TEAM = 5;        //最小分组单位
const long long INF = (long long)1 << 32;
long long y[MOUNT];

void PRINT(long long* num, int start, int end)
{
	/*
	for (int i = start; i < end + 1; i++)
	{
		cout << num[i] << " ";
	}
	cout << endl;
	//*/
}

int compare(const void * a, const void * b)
{
	long long result = (*(long long *)a - *(long long *)b);
	if (result < 0)
		return -1;
	if (result == 0)
		return 0;
	return 1;
}

int partition(long long* a, int p, int r, long long x)
{
	int i = p - 1, j = r + 1;
	while (a[++i] != x);
	swap(a[i], a[p]);
	i = p;
	while (true)
	{
		while (a[++i] < x);
		while (a[--j] > x);
		if (i >= j)
		{
			break;
		}
		swap(a[i], a[j]);
	}
	swap(a[p], a[j]);
	return j;
}

void divide_TEAM(long long *num, int start, int end)
{
	//将元素每5个分成一组，分别排序，并将该组中位数与a[start+i]交换位置
	int i = 0, k = start;
	for (; i < (end + 1 - start) / TEAM; i++, k += TEAM)
	{
		qsort(num + k, TEAM, sizeof(long long), compare);
		swap(num[k + TEAM / 2], num[start + i]);
	}
	return;
}

long long find_nth_element(long long *num, int start, int end, int nth)//第1小开始
{
	if (end - start < 75)
	{
		qsort(num + start, end - start + 1, sizeof(long long), compare);
		return num[start + nth - 1];
	}
	//将元素每5个分成一组，分别排序，并将该组中位数与a[start+i]交换位置
	divide_TEAM(num, start, end);

	//找中位数的中位数
	long long pivot = find_nth_element(num, start, start + (end + 1 - start) / TEAM - 1, (end + 1 - start) / (2 * TEAM));
	//cout << "pivot:" << pivot << endl;
	PRINT(num, start, end);
	//按照pivot进行排序
	int k = partition(num, start, end, pivot);
	PRINT(num, start, end);
	int j = k - start + 1;
	if (nth == j)
		return num[k];
	if (nth < j)
		return find_nth_element(num, start, k - 1, nth);
	else
		return find_nth_element(num, k + 1, end, nth - j);
}

int main()
{
	//*
	//这是测试代码
	int size = 550;//多少个测试数据
	int k = 500;//输出第k小的数字
	srand((unsigned)time(0));

	for (int i = 0; i < size; i++)
	{
		y[i] = rand() % 2100;
		//cout << y[i] << endl;
	}

	cout << "第" << k  << "小元素是" << find_nth_element(y, 0, size - 1, k) << endl;

	//重新排序，对比结果
	qsort(y, size, sizeof(long long), compare);

	cout << "y[" << k - 1 << "]=" << y[k - 1] << endl;
	
	//*/


	/*
	long long xx, yy;
	int i = 0;
	while (~scanf("%lld%*c%lld", &xx, &yy))
	{

		y[i++] = yy;
	}
	cout << find_nth_element(y, 0, i - 1, (i + 1) / 2) << endl;
	//*/
	return 0;
}