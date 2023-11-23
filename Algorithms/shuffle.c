#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

void shuffle(int* arr, int num) {
    srand(time(NULL));
    int temp, rn;
    for (int i = 0; i < num - 1; i++) {
        rn = rand() % (num - i) + i;  // i ���� num-1 ���̿� ������ ���� ����
        temp = arr[i];
        arr[i] = arr[rn];
        arr[rn] = temp;
    }
}

void print_list(int* arr, int num) {
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}