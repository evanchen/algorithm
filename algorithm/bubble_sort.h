#pragma once
#include"util.h"

//ð������, O(1+2+...+n-1) = O(n2)
void bubble_sort(int* arr, int size)
{
	bool isinorder = true; //�Ż�
	for (int i = size; i > 0; i--) {
		isinorder = true;
		for (int j = 0; j < i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				isinorder = false;
			}
		}
		print(arr, size);
		if (isinorder) break;
	}
}
