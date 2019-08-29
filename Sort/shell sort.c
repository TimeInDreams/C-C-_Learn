void ShellSort(ElementType *arr, int *increment, int len_arr, int len_increment)//这里假定increment数组是按从大到小的顺序
{
	for (int i = 0; i < len_increment; i++)
	{
		for (int incre = increment[i], j = 0; j < len_arr - incre; j++)
		{
			for (int k = j + incre; k < len_arr; k += incre)
			{
				if (arr[k - incre] < arr[k])
					swap(arr[k - incre], arr[k]);
			}
		}
	}
	return;
}