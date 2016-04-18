#pragma once
#include"util.h"

int partition(int* arr, int bpos, int epos)
{
	int tarPos = bpos;
	int key = arr[bpos];
	while (bpos < epos)
	{
		if (arr[bpos] > arr[epos]) {
			swap(&arr[bpos], &arr[epos]);
			if (tarPos == bpos) {
				bpos++;
				tarPos = epos;
			}
			else
			{
				epos--;
				tarPos = bpos;
			}
		}
		else {
			if (bpos == tarPos)
				epos--;
			else
				bpos++;
		}
	}
	print(arr, 10);
	return tarPos;
}

void do_quick_sort(int* arr, int bpos, int epos)
{
	if (bpos >= epos) return;
	int m = partition(arr, bpos, epos);
	do_quick_sort(arr, bpos,m);
	do_quick_sort(arr, m + 1,epos);
}

//��������,���η�,��Ⱥϲ���������ʱ����Ҫ����������
void quick_sort(int* arr, int size)
{
	do_quick_sort(arr, 0, size - 1);
}

