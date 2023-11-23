#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

void quicksort_DC(int list[], int low, int high) {
	int pivot_pos;
	if (low < high) {
		pivot_pos = partition(list, low, high);
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