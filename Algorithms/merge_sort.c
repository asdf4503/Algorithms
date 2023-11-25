#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

//�պ� ���� �Լ�
void merge_sort_DC(int list[], int sorted[], int low, int high) {
    int middle; //�迭�� ������ ������ ���� �߰� ������ �����ϴ� ����
    
    //�迭�� ũ�Ⱑ 1���� ������ ����
    if (low < high) {
        middle = (low + high) / 2;

        //�迭�� ù ��° ������ ��������� ����
        merge_sort_DC(list, sorted, low, middle);
        //�迭�� �� ��° ������ ��������� ����
        merge_sort_DC(list, sorted, middle + 1, high);
        //���ҵ� �� �迭�� �պ��Ͽ� ����
        merge(list, sorted, low, middle, high);
    }
}

//�պ� ���� �Լ�
void merge(int list[], int sorted[], int low, int middle, int high) {
    //�ʱ� �ε��� ����
    int n1 = low, n2 = middle + 1, s = low, i;
    //�� �κ� �迭�� ��ȸ�ϸ鼭 �� ��Ҹ� ���ϰ� ���ĵ� �迭�� ����
    while (n1 <= middle && n2 <= high) {
        //���� �� �κ� �迭�� ��Ҹ� ���Ͽ� �� ���� ���� sorted �迭�� ����
        if (list[n1] <= list[n2]) sorted[s++] = list[n1++];
        else sorted[s++] = list[n2++];
    }
    //ù ��° �κ� �迭�� ���� �ִ� ��� ��Ҹ� ���ĵ� �迭�� ����
    if (n1 > middle) while (n2 <= high) sorted[s++] = list[n2++];
    //�� ��° �κ� �迭�� ���� �ִ� ��� ��Ҹ� ���ĵ� �迭�� ����
    else while (n1 <= middle) sorted[s++] = list[n1++]; 
    //���ĵ� �迭�� ��Ҹ� ������ list �迭�� ����
    for (i = low; i <= high; i++)  list[i] = sorted[i];
}