#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

void shuffle(int *list, int num) {      //�迭�� �������� ���� �Լ�
    srand(time(NULL));                  //�õ� �� ����

    int temp, data;                     //�ӽ� ���� ������ ���� ���� ����
    for (int i = 0; i < num; i++) {     //�������� ����(num)��ŭ �ݺ� ����
        data = rand() % (num - i) + i;  //i ���� num ���̿� ������ ���� ����
        //�迭 ��ġ ����
        temp = list[i];                 
        list[i] = list[data];
        list[data] = temp;
    }
}

void print_list(int *list, int num) {   //�迭 ��� �Լ�
    for (int i = 0; i < num; i++) {     //�������� ����(num)��ŭ �ݺ� ����
        printf("%d ", list[i]);         //�迭 ���
    }
    printf("\n");
}