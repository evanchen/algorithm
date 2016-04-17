#pragma once
#include"util.h"

//��������, O(1+2+...+n-1) = O(n2)
//����Ƚ������һ��Ԫ�ز���ȷ���������,������ǰȷ�����ź���,���ٲ���Ҫ��ѭ��
//1.take the first element of the unsorted part, and
//2.place it at the correct position in the sorted part.
//Most time is spent on repeatedly placing the first element of the unsorted part at the correct place in the sorted part.
void insert_sort(int* arr, int size)
{
	int key = 0;
	int j = 0;
	for (int i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		print(arr, size);
	}
}
