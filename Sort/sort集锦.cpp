#include <iostream>
using namespace std;

const int N = 1E3;
const int CutOff = 3;
typedef int ElementType;

void InsertionSort(ElementType *arr, int NumOfElements)
{
	int p, j;
	for (p = 1; p < NumOfElements; ++p)
	{
		ElementType tmp = *(arr + p);
		for (j = p; j > 0 && *(arr + j - 1) > tmp; --j)
		{
			*(arr + j) = *(arr + j - 1);
		}
		*(arr + j) = tmp;
	}
	return;
}

ElementType Median3(ElementType *arr, int left, int right)
{
	int center = (left + right) / 2;
	if (arr[left] > arr[center])
	{
		swap(arr[left], arr[center]);
	}
	if (arr[center] > arr[right])
	{
		swap(arr[center], arr[right]);
	}
	if (arr[left] > arr[center])
	{
		swap(arr[left], arr[center]);
	}
	//arr[left] < arr[center] < arr[right]
	swap(arr[center], arr[right - 1]);//hide pivot
	return arr[right - 1];
}

void QSort(ElementType *arr, int left, int right)
{
	if (left + CutOff > right)
	{
		ElementType pivot = Median3(arr, left, right);
		int i = left, j = right;
		while (true)
		{
			while (arr[++i] < pivot);
			while (arr[--j] > pivot);
			if (i < j)
				swap(arr[i], arr[j]);
			else
				break;
		}
		swap(arr[i], arr[right - 1]);
		QSort(arr, left, i - 1);
		QSort(arr, i + 1, right);//restore pivot
	}
	else
	{
		InsertionSort(arr + left, right - left + 1);
	}
	return;
}

void QuickSort(ElementType *arr, int NumOfElements)
{
	QSort(arr, 0, NumOfElements - 1);
	return;
}

void ShellSort(ElementType *arr, int NumOfElements)
{
	int i, j, increment;
	ElementType tmp;
	for (increment = NumOfElements >> 1; increment > 0; increment >>= 1)
	{
		for (i = increment; i < NumOfElements; ++i)
		{
			tmp = arr[i];
			for (j = i; j >= increment; j -= increment)
			{
				if (arr[j] < arr[j - increment])
					arr[j] = arr[j - increment];
				else
					break;
			}
			arr[j] = tmp;
		}
	}
	return;
}

void PercolateDown(ElementType *arr, int index, int NumOfEmelents)
{
	//max heap
	int i = 0, child = 0;
	ElementType FiretElement = arr[index];
	for (i = index; 2 * i + 1 < NumOfEmelents; i = child)
	{
		child = 2 * i + 1;
		if (child + 1 < NumOfEmelents && arr[child + 1] > arr[child])
			child++;
		if (FiretElement > arr[child])
		{
			break;
		}
		else
			arr[i] = arr[child];
	}
	arr[i] = FiretElement;
	return;
}

void HeapSort(ElementType *arr, int NumOfElements)
{
	for (int i = NumOfElements / 2; i >= 0; --i)
	{
		//buid heap
		PercolateDown(arr, i, NumOfElements);
	}
	for (int i = NumOfElements - 1; i > 0; --i)
	{
		swap(arr[0], arr[i]);
		PercolateDown(arr, 0, i);
	}
	return;
}

void Merge(ElementType *arr, ElementType *tmparr, int Lpos, int Rpos, int Rend)
{
	int Lend = Rpos - 1;
	int tmppos = Lpos;
	int numElements = Rend - Lpos + 1;
	while (Lpos <= Lend && Rpos <= Rend)
	{
		if (arr[Lpos] < arr[Rpos])
			tmparr[tmppos++] = arr[Lpos++];
		else
			tmparr[tmppos++] = arr[Rpos++];
	}
	while (Lpos <= Lend)
	{
		tmparr[tmppos++] = arr[Lpos++];
	}
	while (Rpos <= Rend)
	{
		tmparr[tmppos++] = arr[Rpos++];
	}
	for (int i = 0; i < numElements; ++i, --Rend)
		arr[Rend] = tmparr[Rend];
	return;
}

void MSort(ElementType *arr, ElementType *tmparr, int left, int right)
{
	if (right > left)
	{
		int center = (left + right) / 2;
		MSort(arr, tmparr, left, center);
		MSort(arr, tmparr, center + 1, right);
		Merge(arr, tmparr, left, center + 1, right);
	}
	return;
}

void MergeSort(ElementType *arr, int NumOfElements)
{
	ElementType *tmparr = new ElementType[NumOfElements];
	MSort(arr, tmparr, 0, NumOfElements - 1);
	return;
}

int main()
{
	ElementType arr[N];
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}

	MergeSort(arr, n);

	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}

	cout << endl;

	return 0;
}