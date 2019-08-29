/*
要求根据给定输入，按照课堂给定的快速排序算法进行排序，输出排序结果和median3的返回值。

 注：1,cutoff值为5，不足cutoff使用插入排序。

		2,输入、输出格式参见测试用例0。
*/
#include "pch.h"
#include <iostream>
#include <string>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
const int INF = 1e5;
const int N = 1e2;
const int cutoff = 5;
int median3[N];//需要将其初始化为INF
int medianOfThree(int *arr, int start, int end)
{
	int middle = (start + end) / 2;
	if (arr[start] > arr[middle])
		swap(arr[middle], arr[start]);
	if (arr[start] > arr[end])
		swap(arr[start], arr[end]);
	if (arr[middle] > arr[end])
		swap(arr[middle], arr[end]);
	/*Invariant: arr[start] <= arr[middle] <= arr[end]*/
	swap(arr[middle], arr[end - 1]);/*hide pivot*/
	/*only need to sort arr[start+1]...arr[end-2]*/
	int i = 0;
	while (median3[i] != INF)i++;
	median3[i] = arr[end - 1];
	return median3[i];
}
int partition(int *arr, int start, int end)
{
	int pivot = medianOfThree(arr, start, end);
	int i = start, j = end - 1;
	while (i < j)
	{
		/*这里实际上是对arr[start+1]...arr[end-1]进行排序,pivot==arr[end-1]*/
		while (arr[++i] <= pivot);
		while (arr[--j] > pivot);
		if (i < j)
		{
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i], arr[end - 1]);
	/*
	for (j = start; j <= end; j++)
	{
		cout << arr[j] << " ";
	}
	cout << "  i=" << i <<  "  pivot=" << pivot << endl;
	//*/
	return i;
}
void insertSort(int *arr, int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		for (int j = i; arr[j] < arr[j - 1] && j > start; j--)
		{
			swap(arr[j], arr[j - 1]);
		}
	}
	return;
}
void quickSort(int *arr, int start, int end)
{
	if (start + cutoff <= end)
	{
		int index = partition(arr, start, end);
		quickSort(arr, start, index - 1);
		quickSort(arr, index + 1, end);
	}
	else
		insertSort(arr, start, end);/*数据较少时，insertSort更快速*/
	return;
}
int main()
{
	for (int i = 0; i < N; i++)
		median3[i] = INF;
	int arr[N];
	int len = 0;
	while (true)
	{
		string s;
		cin >> s;
		if (s[0] == '#')
			break;
		arr[len++] = stoi(s);
	}

	quickSort(arr, 0, len - 1);


	cout << "After Sorting:\n";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\nMedian3 Value:\n";
	if (median3[0] == INF)
		cout << "none\n";
	else
	{
		int i = 0;
		while (median3[i] != INF)
			cout << median3[i++] << " ";
		cout << endl;
	}
	return 0;
}