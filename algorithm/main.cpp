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

//��������, O(1+2+...+n-1) = O(n2)
//����Ƚ������һ��Ԫ�ز���ȷ���������,������ǰȷ�����ź���,���ٲ���Ҫ��ѭ��
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

//ѡ������,O(n-1 + n-2 + .. + 1) = O(n2)
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

//ð������, O(1+2+...+n-1) = O(n2)
void bubble_sort(int* arr, int size)
{
	bool isinorder = true; //�Ż�
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

//�ϲ�����
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

//�ϲ������Ż�
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

//�Ӵ�ƥ��: ���ַ���ѯ
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
			i = i - j + 1;	//�����ص���ʼ����һλ
			j = 0;//�Ӵ��ص�0
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

//���ֵjΪģʽ��ʧ���λ��,����k������p0 p1 ... pk-1 = pj-k pj-k+1 ... pj-1�����൱��next[j] = k.
//next[j] = k ����p[j] ֮ǰ��ģʽ���Ӵ��У��г���Ϊk ����ͬǰ׺�ͺ�׺���������next ���飬
//��KMPƥ���У���ģʽ����j �����ַ�ʧ��ʱ����һ����next[j]�����ַ��������ı���ƥ�䣬�൱��ģʽ�������ƶ�j - next[j] λ��

/* :TODO: �Ľ�:
������ڲ��ó���p[j] = p[ next[j] ]��Ϊʲô�أ������ǣ���p[j] != s[i] ʱ��
�´�ƥ���Ȼ��p[ next [j]] ��s[i]ƥ�䣬���p[j] = p[ next[j] ]����Ȼ���º�һ��ƥ��ʧ�ܣ���Ϊp[j]�Ѿ���s[i]ʧ�䣬
Ȼ���㻹�ø�p[j]��ͬ��ֵp[next[j]]ȥ��s[i]ƥ�䣬����Ȼ����Ȼʧ�䣩��
���Բ�������p[j] = p[ next[j ]]�����������p[j] = p[ next[j] ]զ���أ�
��������ˣ�����Ҫ�ٴεݹ飬����next[j] = next[ next[j] ]��
*/

void get_next(const char* sub, int next[])
{
	int subLen = strlen(sub);
	int maxLen = 0;
	for (int i = 0; i < subLen-1; i++) { //i���Ӵ�ĩ��λ��
		maxLen = 0;
		for (int j = 0; j < i; j++) { //��ÿ���Ӵ������Ӵ����ͬǰ��׺
			if (str_cmp(sub, 0, j, i - j, i)) {
				if (j + 1 > maxLen)
					maxLen = j + 1;
			}
		}
		next[i] = maxLen;
	}
}

//:TODO: get_next����һ�ֽⷨ,��ƥ��Ĺ��̺�kmp_substringһ��,ֻ��������ǰ׺��Ϊģʽ��
void get_next2(const char* sub, int next[])
{
	int subLen = strlen(sub);
	int i = 0;
	int j = 1; //��ʼ���Ӵ������һ���͵ڶ����ַ��Ƚ�
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
				if (i == next[j - 1]) { //��ǰʧ��,��ʧ������һ��λ�û���i�Ļ�,�´�ƥ���Ȼ����Ҫʧ��,ʧ�������ζ����ʧ��λ�õ���һλnextֵ
					i = next[i - 1];
				}
				else {
					i = next[j - 1]; //�ƶ�ģʽ��
				}
			}
		}
	}
}

//kmp�㷨: ƥ��ʧ��ʱ,��ģʽ��sub��Ѱ����󳤶��Ӵ���ǰ׺��׺,����������λ��,�����Ӵ�����һ��ƥ��λ��
//�ص�����λ�ȡnext,��ʧ��λ�õ���һλ������󳤶�k����ǰ��׺�Ӵ�,k+1����sub�Ӵ��¸�Ҫ��������ǰƥ��λ�öԱȵ�λ��
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
		else { //����λ��i �� ģʽ��λ��j ʧ��,�ҳ�ģʽ��jλ�õ���һ�ַ�,��֪0..j-1������ƥ�䵽i-1,��ô�ҳ�0..j-1�Ӵ�����󳤶�ģʽ������ǰ��׺,�ƶ�j��i�ٴ�ƥ��
			if (j == 0) //��ģʽ�������λ�û���ƥ��ʧ��,���ƶ�����
				i++; 
			else 
				j = next[j-1]; //�ƶ�ģʽ��
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