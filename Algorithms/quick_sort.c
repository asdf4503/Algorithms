#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

//�� ���� �Լ�
void quicksort_DC(int list[], int low, int high, int threshold) {
	//�迭�� ũ�Ⱑ 1�̻��� �� ����
	if (low < high) {
		// ������ ��� ����(�迭�� ũ�Ⱑ �Ӱ谪���� ū ��쿡�� ������ ����)
		if (high - low > threshold) {  
			int pivot_pos = partition(list, low, high, threshold); //�迭�� �����ϰ� �Ǻ��� ��ġ�� ã��
			//�Ǻ��� �������� ���ʰ� ������ �κ� �迭�� ���� ��������� �� ���� ����
			quicksort_DC(list, low, pivot_pos - 1, threshold);
			quicksort_DC(list, pivot_pos + 1, high, threshold);
		}
		else {
			insertion_Sort(list, low, high);	// �Ӱ谪 ������ ��� ���� ���� ���
		}
	}
}

//�迭�� �����ϰ� �Ǻ��� ��ġ�� ã�� �Լ�
int partition(int list[], int low, int high, int threshold) {
	int i, j = low;
	int temp = 0;
	for (i = low + 1; i <= high; i++) {
		//�Ǻ����� ���� ���� ������ j�� ������Ű�� ���� ��ȯ
		if (list[i] < list[low]) {
			j++;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	//�Ǻ� ��ġ ����
	temp = list[low];
	list[low] = list[j];
	list[j] = temp;

	return j;	//pivot�� ��ġ�� ��ȯ
}

// ���� ���� �Լ�
void insertion_Sort(int list[], int low, int high) {
	int i, j, next;
	for (i = low + 1; i <= high; i++) {
		next = list[i];
		for (j = i - 1; j >= 0 && next < list[j]; j--)
			list[j + 1] = list[j];
		list[j + 1] = next;
	}
}
