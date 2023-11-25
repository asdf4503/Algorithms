#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "shuffle.h"
#include "quicksort.h"
#include "shuffle.h"

int main(void) {
    int data;           //������ ������ �����ϴ� ����
    int *list_merge;    //�պ� ���Ŀ� ���� �迭 ������
    int *list_quick;    //�� ���Ŀ� ���� �迭 ������
    
    //������ �Է�
    printf("������ ������ �Է��Ͻÿ�. : ");
    scanf("%d", &data);
    printf("\n");

    //�����͸� ������ �迭 �Ҵ�
    list_merge = (int*)malloc(sizeof(int) * data);
    list_quick = (int*)malloc(sizeof(int) * data);

    printf("������ ���� ��\n"); 
    int i;
    //�ʱ� ������ ����
    for (i = 0; i < data; i++) {
        list_merge[i] = i + 1;
        list_quick[i] = i + 1;
    }
    //�������� ��ġ�� �������� ����
    shuffle(list_merge, data);

    //���� �����͸� ����ϱ� ���� ����
    for (i = 0; i < data; i++) {
        list_quick[i] = list_merge[i];
    }
    printf("������ ���� �Ϸ�\n");

    //�պ� ���� ����
    printf("\n�պ����� ����\n");
    clock_t start_merge = clock();  //�պ� ���� ���� �ð� ���� ����
    merge_sort_DC(list_merge, 0, data - 1); 

    clock_t end_merge = clock();    //�պ� ���� ���� �ð� ���� ����
    //print_list(list_merge, data); //�պ� ���� ��� ���

    //�պ� ���� ���� �ð� ���
    printf("�ҿ� �ð�: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);

    free(list_merge);               //�պ� ���� �迭 �޸� �Ҵ� ����

    //�� ���� ����
    printf("������ ����\n");
    printf("�Ǻ� : %d\n", list_quick[0]);     //�Ǻ� ���
    clock_t start_quick = clock();            //�� ���� ���� �ð� ���� ����
    quicksort_DC(list_quick, 0, data - 1, 10);

    clock_t end_quick = clock();    //�� ���� ���� �ð� ���� ����
    //print_list(list_quick, data); //�� ���� ��� ���
    //�� ���� ���� �ð� ���
    printf("�ҿ� �ð�: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);

    free(list_quick);           //�� ���� �迭 �޸� �Ҵ� ����

    return 0;
}
