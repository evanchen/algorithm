#pragma once
#include"util.h"

int partition(int* arr, int bpos, int epos)
{
	int tarPos = bpos;
	int key = arr[tarPos];
	while (bpos < epos)
	{
		if (arr[tarPos] > arr[epos]) {
			arr[epos] = arr[tarPos];
			bpos;
		}
	}
}

void do_quick_sort(int* arr, int bpos, int epos)
{
	if (bpos <= epos) return;
	int m = partition(arr, bpos, epos);
	do_quick_sort(arr, bpos,m);
	do_quick_sort(arr, m + 1,epos);
}

//��������,���η�,��Ⱥϲ���������ʱ����Ҫ����������
void quick_sort(int* arr, int size)
{
	do_quick_sort(arr, 0, size - 1);
}

