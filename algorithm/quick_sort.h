#pragma once
#include"util.h"

int partition(int* arr, int bpos, int epos)
{
	int tarPos = bpos;
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

//Let k < l. Suppose Partition(A[k..l]) returns m.
// 1. k <= m < l;
// 2.Partition yields a permutation of the original list,
// where A[k..m] contains only numbers <= A[k]
// and A[m + 1..l] contains only numbers >= A[k].
int partition2(int* arr, int bpos, int epos)
{
	int keyPos = bpos;
	bpos--;
	epos++;
	while (bpos < epos)
	{
		bpos++;
		while (arr[bpos] < arr[keyPos])
			bpos++;
		epos--;
		while (arr[epos] > arr[keyPos])
			epos--;
		if (bpos < epos)
			swap(&arr[bpos], &arr[epos]);
	}
	print(arr, 10);
	return epos;
}

void do_quick_sort(int* arr, int bpos, int epos)
{
	if (bpos >= epos) return;
	int m = partition(arr, bpos, epos);
	do_quick_sort(arr, bpos,m);
	do_quick_sort(arr, m + 1,epos);
}

//��������,���η�,��Ⱥϲ���������ʱ����ֱ����ԭ����������
// ƽ�� O(log2n)  * O(n) = O(n*log2n)
// ��������,arr�������� O(n2)
// partition �������ֿ��Լ���ƽ����ʱ
void quick_sort(int* arr, int size)
{
	do_quick_sort(arr, 0, size - 1);
}

