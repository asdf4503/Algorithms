#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

//합병 정렬 함수
void merge_sort_DC(int list[], int sorted[], int low, int high) {
    int middle; //배열을 반으로 나누기 위한 중간 지점을 저장하는 변수
    
    //배열의 크기가 1개일 때까지 분할
    if (low < high) {
        middle = (low + high) / 2;

        //배열의 첫 번째 절반을 재귀적으로 정렬
        merge_sort_DC(list, sorted, low, middle);
        //배열의 두 번째 절반을 재귀적으로 정렬
        merge_sort_DC(list, sorted, middle + 1, high);
        //분할된 두 배열을 합병하여 정렬
        merge(list, sorted, low, middle, high);
    }
}

//합병 정렬 함수
void merge(int list[], int sorted[], int low, int middle, int high) {
    //초기 인덱스 설정
    int n1 = low, n2 = middle + 1, s = low, i;
    //두 부분 배열을 순회하면서 각 요소를 비교하고 정렬된 배열에 복사
    while (n1 <= middle && n2 <= high) {
        //현재 두 부분 배열의 요소를 비교하여 더 작은 값을 sorted 배열에 복사
        if (list[n1] <= list[n2]) sorted[s++] = list[n1++];
        else sorted[s++] = list[n2++];
    }
    //첫 번째 부분 배열에 남아 있는 모든 요소를 정렬된 배열로 복사
    if (n1 > middle) while (n2 <= high) sorted[s++] = list[n2++];
    //두 번째 부분 배열에 남아 있는 모든 요소를 정렬된 배열로 복사
    else while (n1 <= middle) sorted[s++] = list[n1++]; 
    //정렬된 배열의 요소를 원래의 list 배열로 복사
    for (i = low; i <= high; i++)  list[i] = sorted[i];
}