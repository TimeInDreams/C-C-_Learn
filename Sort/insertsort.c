void InsertionSort(ElementType *arr, ElementType input)
{
	int i = strlen(arr);
	while(i>0)
	{
		if (input < arr[i])
		{
			arr[i + 1] = a[i];
			i--;
		}
		else break;
	}
	a[i] = input;
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
