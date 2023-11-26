#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

//퀵 정렬 함수
void quicksort_DC(int list[], int low, int high, int threshold) {
	//퀵정렬 사용 조건 (배열의 크기가 임계값보다 큰 경우에만 퀵정렬 수행)
	if (high - low > threshold) {  
		int pivot_pos = partition(list, low, high); //배열을 분할하고 피봇의 위치를 찾음
		//피봇을 기준으로 왼쪽과 오른쪽 부분 배열에 대해 재귀적으로 퀵 정렬 수행
		if(low < pivot_pos - 1)quicksort_DC(list, low, pivot_pos - 1, threshold);
		if(pivot_pos + 1 < high)quicksort_DC(list, pivot_pos + 1, high, threshold);
	}
	else {
		insertion_Sort(list, low, high);	//임계값 이하인 경우 삽입 정렬 사용
	}	
}

//배열을 분할하고 피봇의 위치를 찾는 함수
int partition(int list[], int low, int high) {
	int i, j = low;	//i는 순회 인덱스, j는 피봇보다 작은 값들의 인덱스
	int temp = 0;	//값 교환을 위한 임시 변수
	for (i = low + 1; i <= high; i++) {
		//피봇보다 작은 값을 만나면 j를 증가시키고 값을 교환
		if (list[i] < list[low]) {
			j++;
			//list[i]와 list[j] 교환
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	//list[low]와 list[j] 교환
	temp = list[low];
	list[low] = list[j];
	list[j] = temp;

	return j;	//pivot의 위치를 반환
}

//삽입 정렬 함수
void insertion_Sort(int list[], int low, int high) {
	int i, j, next;	//i와 j는 순회 인덱스, next는 현재 정렬할 요소
	for (i = low + 1; i <= high; i++) {
		next = list[i];
		//현재 요소(next)를 이미 정렬된 배열의 적절한 위치로 이동
		for (j = i - 1; j >= 0 && next < list[j]; j--)
			list[j + 1] = list[j];
		list[j + 1] = next;	//현재 요소를 최종 위치에 삽입
	}
}
