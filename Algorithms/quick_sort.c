#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

//퀵 정렬 함수
void quicksort_DC(int list[], int low, int high, int threshold) {
	//배열의 크기가 1이상일 때 실행
	if (low < high) {
		// 퀵정렬 사용 조건(배열의 크기가 임계값보다 큰 경우에만 퀵정렬 수행)
		if (high - low > threshold) {  
			int pivot_pos = partition(list, low, high, threshold); //배열을 분할하고 피봇의 위치를 찾음
			//피봇을 기준으로 왼쪽과 오른쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
			quicksort_DC(list, low, pivot_pos - 1, threshold);
			quicksort_DC(list, pivot_pos + 1, high, threshold);
		}
		else {
			insertion_Sort(list, low, high);	// 임계값 이하인 경우 삽입 정렬 사용
		}
	}
}

//배열을 분할하고 피봇의 위치를 찾는 함수
int partition(int list[], int low, int high, int threshold) {
	int i, j = low;
	int temp = 0;
	for (i = low + 1; i <= high; i++) {
		//피봇보다 작은 값을 만나면 j를 증가시키고 값을 교환
		if (list[i] < list[low]) {
			j++;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	//피봇 위치 변경
	temp = list[low];
	list[low] = list[j];
	list[j] = temp;

	return j;	//pivot의 위치를 반환
}

// 삽입 정렬 함수
void insertion_Sort(int list[], int low, int high) {
	int i, j, next;
	for (i = low + 1; i <= high; i++) {
		next = list[i];
		for (j = i - 1; j >= 0 && next < list[j]; j--)
			list[j + 1] = list[j];
		list[j + 1] = next;
	}
}
