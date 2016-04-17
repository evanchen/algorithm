#pragma once
#include"util.h"

//—°‘Ò≈≈–Ú,O(n-1 + n-2 + .. + 1) = O(n2)
//1.search for a smallest element in the unsorted part of the list,
//2.swap this element with the first element in the unsorted part of the list, and
//3.exclude this element from the unsorted part of the list.
//Most time is spent on repeatedly finding a smallest element in the unsorted part.
void select_sort(int* arr, int size)
{
	int j = 0;
	int idx = 0;
	for (int i = 0; i < size - 1; i++) {
		j = i + 1;
		idx = j;
		for (; j < size - 1; j++) {
			if (arr[idx] > arr[j + 1]) {
				idx = j + 1;
			}
		}
		if (arr[idx] < arr[i]) {
			swap(&arr[idx], &arr[i]);
		}
		print(arr, size);
	}
}
