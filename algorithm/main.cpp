#include<iostream>

const int SIZE = 10;
int unsort_arr[SIZE] = { 5,1,3,6,9,5,10,4,7,2};
void print(int* arr,int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ",";
	std::cout << std::endl;
}

void swap(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

//插入排序, O(1+2+...+n-1) = O(n2)
//必须比较完最后一个元素才能确定排序完成,不能提前确定已排好序,减少不必要的循环
//1.take the first element of the unsorted part, and
//2.place it at the correct position in the sorted part.
//Most time is spent on repeatedly placing the first element of the unsorted part at the correct place in the sorted part.
void insert_sort(int* arr, int size)
{
	int key = 0;
	int j = 0;
	for (int i = 1; i < size; i++)	{
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

//选择排序,O(n-1 + n-2 + .. + 1) = O(n2)
//1.search for a smallest element in the unsorted part of the list,
//2.swap this element with the first element in the unsorted part of the list, and
//3.exclude this element from the unsorted part of the list.
//Most time is spent on repeatedly finding a smallest element in the unsorted part.
void select_sort(int* arr, int size)
{
	int j = 0;
	int idx = 0;
	for (int i = 0; i < size-1; i++)	{
		j = i + 1;
		idx = j;
		for (; j < size-1; j++) {
			if (arr[idx] > arr[j + 1]) {
				idx = j + 1;
			}
		}
		if (arr[idx] < arr[i]) {
			swap(&arr[idx], &arr[i]);
		}
		print(unsort_arr, SIZE);
	}
}

//冒泡排序, O(1+2+...+n-1) = O(n2)
void bubble_sort(int* arr, int size)
{
	bool isinorder = true; //优化
	for (int i = size; i > 0; i--) {
		isinorder = true;
		for (int j = 0; j < i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				isinorder = false;
			}
		}
		print(unsort_arr, SIZE);
		if (isinorder) break;
	}
}

//合并排序
int* do_merge(int* arr1, int size1,int* arr2,int size2)
{
	int bpos1 =0, bpos2 = 0,
	int* tmp = (int*)malloc((size1 + size2) * sizeof(int));
	int i = 0;
	while(bpos1 < size1 && bpos2 < size2) {
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

int* do_merge_sort(int* arr, int bpos,int size)
{
	if (size == 1) {
		int* tmp = (int*)malloc(size * sizeof(int));
		tmp[0] = arr[bpos];
		return tmp;
	}
	int mid = size / 2;
	int* ret1 = do_merge_sort(arr, bpos,mid);
	int* ret2 = do_merge_sort(arr, bpos + mid,size - mid);
	if (!ret1)
		return ret2;
	else if (!ret2)
		return NULL;
	int* ret3 = do_merge(ret1, mid,ret2,size-mid);
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

//合并排序优化
void do_merge(int* arr, int first, int mid, int last, int* tmp)
{
	int bpos1 = first;
	int epos1 = mid-1;
	int bpos2 = mid;
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
		do_merge_sort2(arr, first, mid - 1, tmp);
		do_merge_sort2(arr, mid, last, tmp);
		do_merge(arr, first, mid, last, tmp);
	}
}

void merge_sort2(int* arr, int size)
{
	int* tmp = (int*)malloc(size * sizeof(int));
	memset(tmp, 0, size*sizeof(int));
	do_merge_sort2(arr, 0, size-1, tmp);
	print(arr, size);
}

//子串匹配: 逐字符轮询
int substring(const char* str, const char* sub, int pos)
{
	int strLen = strlen(str);
	int subLen = strlen(sub);
	if (subLen > strLen || pos < 0 || pos >= strLen) return -1;
	int i = pos;
	int j = 0;
	while (i < strLen && j < subLen) {
		if (str[i] == sub[j]) {
			i++; j++;
		}
		else {
			i = i - j + 1;	//主串回到开始的下一位
			j = 0;//子串回到0
		}
	}
	if (j == subLen) return (i - j);
	return -1;
}


bool str_cmp(const char* src, int pos1,int pos2, int pos3, int pos4)
{
	for (; pos1 <= pos2 && pos3 <= pos4; pos1++,pos3++) {
		if (src[pos1] != src[pos3])
			return false;
	}
	return true;
}

//如果值j为模式串失配的位置,对于k，已有p0 p1 ... pk-1 = pj-k pj-k+1 ... pj-1，则相当于next[j] = k.
//next[j] = k 代表p[j] 之前的模式串子串中，有长度为k 的相同前缀和后缀。有了这个next 数组，
//在KMP匹配中，当模式串中j 处的字符失配时，下一步用next[j]处的字符继续跟文本串匹配，相当于模式串向右移动j - next[j] 位。

/* :TODO: 改进:
问题出在不该出现p[j] = p[ next[j] ]。为什么呢？理由是：当p[j] != s[i] 时，
下次匹配必然是p[ next [j]] 跟s[i]匹配，如果p[j] = p[ next[j] ]，必然导致后一步匹配失败（因为p[j]已经跟s[i]失配，
然后你还用跟p[j]等同的值p[next[j]]去跟s[i]匹配，很显然，必然失配），
所以不能允许p[j] = p[ next[j ]]。如果出现了p[j] = p[ next[j] ]咋办呢？
如果出现了，则需要再次递归，即令next[j] = next[ next[j] ]。
*/

void get_next(const char* sub, int next[])
{
	int subLen = strlen(sub);
	int maxLen = 0;
	for (int i = 0; i < subLen-1; i++) { //i是子串末端位置
		maxLen = 0;
		for (int j = 0; j < i; j++) { //对每个子串查找子串最长相同前后缀
			if (str_cmp(sub, 0, j, i - j, i)) {
				if (j + 1 > maxLen)
					maxLen = j + 1;
			}
		}
		next[i] = maxLen;
	}
}

//:TODO: get_next的另一种解法,找匹配的过程和kmp_substring一样,只不过是用前缀作为模式串
void get_next2(const char* sub, int next[])
{
	int subLen = strlen(sub);
	int i = 0;
	int j = 1; //开始由子串本身第一个和第二个字符比较
	while (j < subLen) {
		if (sub[i] == sub[j]) {
			i++; j++;
			next[j-1] = i;
		}
		else { 
			if (i == 0) 
				j++;
			else
			{
				if (i == next[j - 1]) { //当前失配,但失配后的下一个位置还是i的话,下次匹配必然还是要失配,失配就是意味着找失配位置的下一位next值
					i = next[i - 1];
				}
				else {
					i = next[j - 1]; //移动模式串
				}
			}
		}
	}
}

//kmp算法: 匹配失败时,在模式串sub里寻找最大长度子串的前缀后缀,不回溯主串位置,调整子串的下一个匹配位置
//重点在如何获取next,从失配位置的上一位查找最大长度k共有前后缀子串,k+1就是sub子串下个要和主串当前匹配位置对比的位置
int kmp_substring(const char* str, const char* sub, int pos,int next[])
{
	int strLen = strlen(str);
	int subLen = strlen(sub);
	if (subLen > strLen || pos < 0 || pos >= strLen) return -1;
	int i = pos;
	int j = 0;
	while (i < strLen && j < subLen) {
		if (str[i] == sub[j]) {
			i++; j++;
		}
		else { //主串位置i 和 模式串位置j 失配,找出模式串j位置的上一字符,已知0..j-1和主串匹配到i-1,那么找出0..j-1子串中最大长度模式串共有前后缀,移动j与i再次匹配
			if (j == 0) //到模式串的起点位置还是匹配失败,则移动主串
				i++; 
			else 
				j = next[j-1]; //移动模式串
		}
	}
	if (j == subLen) return (i - j);
	return -1;
}

int main()
{
	print(unsort_arr, SIZE);
	merge_sort(unsort_arr, SIZE);
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
	std::cin.get();
	return 0;
}