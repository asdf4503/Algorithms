#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

//합병 정렬 함수
void merge_sort_DC(int list[], int low, int high) {
    int middle;
    if (low < high) {
        middle = (low + high) / 2;

        //첫 번째와 두 번째 반을 재귀적으로 정렬
        merge_sort_DC(list, low, middle);
        merge_sort_DC(list, middle + 1, high);
        merge(list, low, middle, high);
    }
}

//합병 정렬 함수
void merge(int list[], int low, int middle, int high) {
    int i, j, s;
    int n1 = middle - low + 1;
    int n2 = high - middle;

    //동적 메모리 할당으로 임시 배열 생성
    int* left = (int*)malloc(n1 * sizeof(int));
    int* right = (int*)malloc(n2 * sizeof(int));

    //데이터를 임시 배열에 복사
    for (i = 0; i < n1; i++)    left[i] = list[low + i];
    for (j = 0; j < n2; j++)    right[j] = list[middle + 1 + j];

    //임시 배열을 병합하여 원래 배열에 복사
    i = 0; j = 0; s = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            list[s] = left[i];
            i++;
        }
        else {
            list[s] = right[j];
            j++;
        }
        s++;
    }

    //left 배열의 남은 요소들을 복사
    while (i < n1) {
        list[s] = left[i];
        i++;
        s++;
    }

    //right 배열의 남은 요소들을 복사
    while (j < n2) {
        list[s] = right[j];
        j++;
        s++;
    }

    //동적 할당된 메모리 해제
    free(left);
    free(right);
}