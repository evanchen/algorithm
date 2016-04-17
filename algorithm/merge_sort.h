#pragma once
#include"util.h"

//合并排序
int* do_merge(int* arr1, int size1, int* arr2, int size2)
{
	int bpos1 = 0, bpos2 = 0;
	int* tmp = (int*)malloc((size1 + size2) * sizeof(int));
	int i = 0;
	while (bpos1 < size1 && bpos2 < size2) {
		if (arr1[bpos1] <= arr2[bpos2]) {
			tmp[i++] = arr1[bpos1++];
		}
		else {
			tmp[i++] = arr2[bpos2++];
		}
	}
	while (bpos1 < size1)
	{
		tmp[i++] = arr1[bpos1++];
	}
	while (bpos2 < size2)
	{
		tmp[i++] = arr2[bpos2++];
	}
	return tmp;
}

int* do_merge_sort(int* arr, int bpos, int size)
{
	if (size == 1) {
		int* tmp = (int*)malloc(size * sizeof(int));
		tmp[0] = arr[bpos];
		return tmp;
	}
	int mid = size / 2;
	int* ret1 = do_merge_sort(arr, bpos, mid);
	int* ret2 = do_merge_sort(arr, bpos + mid, size - mid);
	if (!ret1)
		return ret2;
	else if (!ret2)
		return NULL;
	int* ret3 = do_merge(ret1, mid, ret2, size - mid);
	print(ret3, size);
	free(ret1);
	free(ret2);
	return ret3;
}

void merge_sort(int* arr, int size)
{
	int* ret = do_merge_sort(arr, 0, size);
	if (ret) {
		for (int i = 0; i < size; i++) {
			arr[i] = ret[i];
		}
		free(ret);
	}
	print(arr, size);
}

void do_merge2(int* arr, int first, int mid, int last, int* tmp)
{
	int bpos1 = first;
	int epos1 = mid;
	int bpos2 = mid + 1;
	int i = 0;
	while (bpos1 <= epos1 && bpos2 <= last) {
		if (arr[bpos1] <= arr[bpos2]) {
			tmp[i++] = arr[bpos1++];
		}
		else {
			tmp[i++] = arr[bpos2++];
		}
	}
	while (bpos1 <= epos1) {
		tmp[i++] = arr[bpos1++];
	}
	while (bpos2 <= last) {
		tmp[i++] = arr[bpos2++];
	}
	for (int j = 0; j < i; j++) {
		arr[first + j] = tmp[j];
	}
}

void do_merge_sort2(int* arr, int first, int last, int* tmp)
{
	if (first < last) {
		int mid = (first + last) / 2;
		do_merge_sort2(arr, first, mid, tmp);
		do_merge_sort2(arr, mid + 1, last, tmp);
		do_merge2(arr, first, mid, last, tmp);
	}
}

//合并排序优化,一种分治法，O(log2n)  * O(n) = O(n*log2n),假设长度为n，分治下去有n次，其中每次需要log2n次排序与合并
void merge_sort2(int* arr, int size)
{
	int* tmp = (int*)malloc(size * sizeof(int));
	memset(tmp, 0, size*sizeof(int));
	do_merge_sort2(arr, 0, size - 1, tmp);
	free(tmp);
	print(arr, size);
}
