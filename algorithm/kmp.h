#pragma once
#include"util.h"
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


bool str_cmp(const char* src, int pos1, int pos2, int pos3, int pos4)
{
	for (; pos1 <= pos2 && pos3 <= pos4; pos1++, pos3++) {
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
	for (int i = 0; i < subLen - 1; i++) { //i���Ӵ�ĩ��λ��
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
			next[j - 1] = i;
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
int kmp_substring(const char* str, const char* sub, int pos, int next[])
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
				j = next[j - 1]; //�ƶ�ģʽ��
		}
	}
	if (j == subLen) return (i - j);
	return -1;
}
