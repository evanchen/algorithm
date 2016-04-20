#pragma once
#include"util.h"

int heap_order(int* arr, int parent, int size)
{
	int left = parent * 2;
	int right = parent * 2 + 1;
	if (left <= size) {
		if (right <= size && arr[left - 1] < arr[right - 1]) {
			left = right;
		}
		if (arr[parent - 1] < arr[left - 1]) {
			swap(&arr[parent - 1], &arr[left - 1]);
			return left;
		}
	}
	return 0;
}

void make_heap(int* arr,int parent, int size)
{
	if (parent >= size) return;
	int left = parent * 2;
	int right = parent * 2 + 1;
	make_heap(arr, left, size);
	make_heap(arr, right, size);
	heap_order(arr, parent, size);
}

void rebuild_order(int* arr, int parent, int size)
{
	if (parent >= size) return;
	int left = parent * 2;
	int right = parent * 2 + 1;
	left = heap_order(arr, parent, size);
	if(left > 0)
		rebuild_order(arr, left, size);
}

//In a binary tree, each node has at most two children.
//The root carries index 1, and if a node has index i ,
//then its children (if any) are indexed 2i and 2i + 1.
//An array of length n gives rise to a binary tree of depth ceil(log2n).

//Finding the largest element in a heap takes O(1).
//Turning an array of length n into a heap takes O(n).
//Replacing the element in the root of a heap, and restoring the heap,takes at most O(log n).
void heap_sort(int* arr, int size)
{
	make_heap(arr, 1, size);
	rebuild_order(arr, 1, size);
	for (int i = size; i > 0; i--) {
		swap(&arr[i-1],&arr[0]);
		rebuild_order(arr, 1, i-1);
	}
	print(arr, 10);
}