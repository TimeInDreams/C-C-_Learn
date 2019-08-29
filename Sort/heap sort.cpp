/*

实验要求：用堆排序算法按关键字递减的顺序排序。

程序输入：待排序记录数（整数）和待排序记录（整数序列）；

程序输出：建堆结果和建堆后第一、第二次筛选结果。（注：待排序记录数大于等于3）


输入
6
11
12
16
14
15
10
输出
16 15 11 14 12 10 
15 14 11 10 12 
14 12 11 10 
*/
#include <iostream>
using namespace std;
void max_heap(int *arr, int len, int dad)
{
    int son = dad * 2;
    while (son < len)
    {
        if (son + 1 < len && arr[son] < arr[son + 1])
            son++;
        if (arr[son] < arr[dad])
            break;
        else
        {
            swap(arr[dad], arr[son]);
        }
        dad = son;
        son = 2 * dad;
    }
    return;
}
void build_heap(int *arr, int len)
{
    for (int i = len / 2; i > 0; i--)
        max_heap(arr, len, i);
    return;
}
void delete_max(int *arr, int len)
{
    swap(arr[len - 1], arr[1]);
}
void print(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return;
}
void sort_heap(int *arr, int len)
{
    //*
    //这里就是进行堆排序的完整步骤，因为这个题目只要求输出两次步骤，因此我们执行下面的代码
    while(len)
    {
        delete_max(arr, len--);
        max_heap(arr, len, 1);//交换第一个与最后一个之后，需要对堆进行维护
		print(arr, len);
    }
    //*/
	/*
    int temp = 2;
    while (temp--)
    {
        delete_max(arr, len--);
        max_heap(arr, len, 1); //交换第一个与最后一个之后，需要对堆进行维护
        print(arr, len);
    }
	//*/
    return;
}
int main()
{
    int n = 0; //代表共有n个整数
    cin >> n;
    int *arr = new int[n + 1]; //为方便进行建堆，第一个arr[0]不存数据
    for (int i = 1; i < n + 1; i++)
    {
        cin >> arr[i];
    }
    build_heap(arr, n + 1);
    print(arr,n+1);
    sort_heap(arr, n + 1);
    return 0;
}
