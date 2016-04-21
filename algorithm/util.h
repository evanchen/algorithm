#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ",";
	std::cout << std::endl;
}

void swap(int* a, int* b)
{
	if (a == b) return;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
