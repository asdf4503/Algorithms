#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

//�� ���� �Լ�
void quicksort_DC(int list[], int low, int high, int threshold) {
	//������ ��� ���� (�迭�� ũ�Ⱑ �Ӱ谪���� ū ��쿡�� ������ ����)
	if (high - low > threshold) {  
		int pivot_pos = partition(list, low, high); //�迭�� �����ϰ� �Ǻ��� ��ġ�� ã��
		//�Ǻ��� �������� ���ʰ� ������ �κ� �迭�� ���� ��������� �� ���� ����
		if(low < pivot_pos - 1)quicksort_DC(list, low, pivot_pos - 1, threshold);
		if(pivot_pos + 1 < high)quicksort_DC(list, pivot_pos + 1, high, threshold);
	}
	else {
		insertion_Sort(list, low, high);	//�Ӱ谪 ������ ��� ���� ���� ���
	}	
}

//�迭�� �����ϰ� �Ǻ��� ��ġ�� ã�� �Լ�
int partition(int list[], int low, int high) {
	int i, j = low;	//i�� ��ȸ �ε���, j�� �Ǻ����� ���� ������ �ε���
	int temp = 0;	//�� ��ȯ�� ���� �ӽ� ����
	for (i = low + 1; i <= high; i++) {
		//�Ǻ����� ���� ���� ������ j�� ������Ű�� ���� ��ȯ
		if (list[i] < list[low]) {
			j++;
			//list[i]�� list[j] ��ȯ
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	//list[low]�� list[j] ��ȯ
	temp = list[low];
	list[low] = list[j];
	list[j] = temp;

	return j;	//pivot�� ��ġ�� ��ȯ
}

//���� ���� �Լ�
void insertion_Sort(int list[], int low, int high) {
	int i, j, next;	//i�� j�� ��ȸ �ε���, next�� ���� ������ ���
	for (i = low + 1; i <= high; i++) {
		next = list[i];
		//���� ���(next)�� �̹� ���ĵ� �迭�� ������ ��ġ�� �̵�
		for (j = i - 1; j >= 0 && next < list[j]; j--)
			list[j + 1] = list[j];
		list[j + 1] = next;	//���� ��Ҹ� ���� ��ġ�� ����
	}
}
