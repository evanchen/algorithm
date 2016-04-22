#include<iostream>
#include"all.h"
const int SIZE = 10;
int unsort_arr[SIZE] = { 5,1,3,6,9,5,10,4,7,2 };
int main()
{
	print(unsort_arr, SIZE);
	//quick_sort(unsort_arr, SIZE);
	/*
	char* str = "BBC ABCDAB ABCDABCDABDE";
	char* sub = "ABCDABD";
	int ret = substring(str, sub, 0);
	printf("%d %s\n", ret,&str[ret]);

	int len = strlen(sub);
	int* next = (int*)malloc(len * sizeof (int));
	memset(next, 0, len* sizeof(int));
	//get_next(sub, next);
	get_next2(sub, next);
	for (int i = 0; i < len; i++) {
		printf("%d,",next[i]);
	}
	printf("\n");
	ret = kmp_substring(str,sub,0,next);
	printf("%d %s\n", ret, &str[ret]);
	*/
	//heap_sort(unsort_arr, SIZE);
	BTree* tree = BuildTree(unsort_arr, SIZE);
	print_tree(tree->root);
	std::cin.get();
	return 0;
}