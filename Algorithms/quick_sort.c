#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

void quicksort_DC(int list[], int low, int high, int threshold) {
	int pivot_pos;
	if (low < high) {
		if (high - low > threshold) {  // ������ ��� ����
			pivot_pos = partition(list, low, high, threshold);
			quicksort_DC(list, low, pivot_pos - 1, threshold);
			quicksort_DC(list, pivot_pos + 1, high, threshold);
		}
		else {
			// �Ӱ谪 ������ ��� ���� ���� ���
			insertion_Sort(list, low, high);
		}
	}
}

int partition(int list[], int low, int high) {
	int i, j = low;
	int temp = 0;
	for (i = low + 1; i <= high; i++) {
		if (list[i] < list[low]) {
			j++;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	temp = list[low];
	list[low] = list[j];
	list[j] = temp;

	return j;
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
