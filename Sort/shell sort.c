void ShellSort(ElementType *arr, int *increment, int len_arr, int len_increment)//����ٶ�increment�����ǰ��Ӵ�С��˳��
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