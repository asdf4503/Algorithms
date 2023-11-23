#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

void merge(int list[], int low, int middle, int high) {
    int i, j, k;
    int n1 = middle - low + 1;
    int n2 = high - middle;

    // 동적 메모리 할당으로 임시 배열 생성
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 데이터를 임시 배열에 복사
    for (i = 0; i < n1; i++)    L[i] = list[low + i];
    for (j = 0; j < n2; j++)    R[j] = list[middle + 1 + j];

    // 임시 배열을 병합하여 원래 배열에 복사
    i = 0; j = 0; k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            list[k] = L[i];
            i++;
        }
        else {
            list[k] = R[j];
            j++;
        }
        k++;
    }

    // L 배열의 남은 요소들을 복사
    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
    }

    // R 배열의 남은 요소들을 복사
    while (j < n2) {
        list[k] = R[j];
        j++;
        k++;
    }

    // 동적 할당된 메모리 해제
    free(L);
    free(R);
}


// 합병 정렬 함수
void merge_sort_DC(int list[], int low, int high) {
    int middle;
    if (low < high) {
        middle = (low + high) / 2;

        // 첫 번째와 두 번째 반을 재귀적으로 정렬
        merge_sort_DC(list, low, middle);
        merge_sort_DC(list, middle + 1, high);
        merge(list, low, middle, high);
    }
}