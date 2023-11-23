#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

void merge(int list[], int low, int middle, int high) {
    int i, j, k;
    int n1 = middle - low + 1;
    int n2 = high - middle;

    // ���� �޸� �Ҵ����� �ӽ� �迭 ����
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // �����͸� �ӽ� �迭�� ����
    for (i = 0; i < n1; i++)    L[i] = list[low + i];
    for (j = 0; j < n2; j++)    R[j] = list[middle + 1 + j];

    // �ӽ� �迭�� �����Ͽ� ���� �迭�� ����
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

    // L �迭�� ���� ��ҵ��� ����
    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
    }

    // R �迭�� ���� ��ҵ��� ����
    while (j < n2) {
        list[k] = R[j];
        j++;
        k++;
    }

    // ���� �Ҵ�� �޸� ����
    free(L);
    free(R);
}


// �պ� ���� �Լ�
void merge_sort_DC(int list[], int low, int high) {
    int middle;
    if (low < high) {
        middle = (low + high) / 2;

        // ù ��°�� �� ��° ���� ��������� ����
        merge_sort_DC(list, low, middle);
        merge_sort_DC(list, middle + 1, high);
        merge(list, low, middle, high);
    }
}