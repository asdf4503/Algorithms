#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

//�պ� ���� �Լ�
void merge_sort_DC(int list[], int low, int high) {
    int middle;
    //������ �������� Ȯ��
    if (low < high) {
        //�߰� ���� ����
        middle = (low + high) / 2;

        //�迭�� ù ��° ������ ��������� ����
        merge_sort_DC(list, low, middle);
        //�迭�� �� ��° ������ ��������� ����
        merge_sort_DC(list, middle + 1, high);
        //���ҵ� �� �迭�� �պ��Ͽ� ����
        merge(list, low, middle, high);
    }
}

//�պ� ���� �Լ�
void merge(int list[], int low, int middle, int high) {
    int i, j, s;
    int n1 = middle - low + 1;
    int n2 = high - middle;

    //���� �޸� �Ҵ����� �ӽ� �迭 ����
    int* left = (int*)malloc(n1 * sizeof(int));
    int* right = (int*)malloc(n2 * sizeof(int));

    //�����͸� �ӽ� �迭�� ����(middle�� �������� ���� ��, ū ��)
    for (i = 0; i < n1; i++)    left[i] = list[low + i];
    for (j = 0; j < n2; j++)    right[j] = list[middle + 1 + j];

    //�� �ӽ� �迭�� ��ҵ��� ���ϸ鼭 ���� �迭�� ����
    i = 0; j = 0; s = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])    list[s++] = left[i++];
        else                        list[s++] = right[j++];
    }

    //left �迭�� ���� ��ҵ��� ����
    while (i < n1)  list[s++] = left[i++];

    //right �迭�� ���� ��ҵ��� ����
    while (j < n2)  list[s++] = right[j++];

    //���� �Ҵ�� �޸� ����
    free(left);
    free(right);
}