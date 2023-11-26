#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "shuffle.h"
#include "quicksort.h"
#include "shuffle.h"

void start() {
    int data;           //������ ������ �����ϴ� ����
    int* list_merge;    //�պ� ���Ŀ� ���� �迭 ������
    int* list_quick;    //�� ���Ŀ� ���� �迭 ������
    int type = 0;

    printf("20191480 �ſ뼱\n");
    //������ �Է�
    printf("������ ������ �Է��Ͻÿ�. : ");
    scanf("%d", &data);
    printf("\n");

    //�����͸� ������ �迭 �Ҵ�
    list_merge = (int*)malloc(sizeof(int) * data);
    list_quick = (int*)malloc(sizeof(int) * data);

    //���� ���α׷� ����
    printf("�պ� ���� : 1 / �� ���� : 2 / ��� : 3\n");
    printf("� ���α׷��� �����Ͻðڽ��ϱ�? : ");
    scanf("%d", &type);

    //���ÿ� �´� ���α׷� ����
    if (type == 1) {
        printf("\n������ ���� ��\n");
        int i;
        //�ʱ� ������ ����
        for (i = 0; i < data; i++)      list_merge[i] = i + 1;
        //�������� ��ġ�� �������� ����
        shuffle(list_merge, data);
        printf("������ ���� �Ϸ�\n");
        /*//������ ���
        printf("\n������ ���\n");
        print_list(list_merge, data); //������ ���*/

        //�պ� ���� ����
        printf("\n�պ����� ����\n");

        clock_t start_merge = clock();  //�պ� ���� ���� �ð� ���� ����
        merge_sort_DC(list_merge, 0, data - 1);
        clock_t end_merge = clock();    //�պ� ���� ���� �ð� ���� ����

        //print_list(list_merge, data); //�պ� ���� ��� ���

        //�պ� ���� ���� �ð� ���
        printf("�ҿ� �ð�: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);
    }
    else if (type == 2) {
        printf("\n������ ���� ��\n");

        int i;
        long threshold;

        //�ʱ� ������ ����
        for (i = 0; i < data; i++)      list_quick[i] = i + 1;
        //�������� ��ġ�� �������� ����
        shuffle(list_quick, data);
        printf("������ ���� �Ϸ�\n");
        //������ ���
        /*printf("\n������ ���\n");
        print_list(list_quick, data);*/

        printf("\n�Ӱ谪�� �����Ͻÿ�. : ");
        scanf("%ld", &threshold);

        //�� ���� ����
        printf("������ ����\n");
        printf("�Ǻ� : %d\n", list_quick[0]);     //�Ǻ� ���

        clock_t start_quick = clock();            //�� ���� ���� �ð� ���� ����
        quicksort_DC(list_quick, 0, data - 1, threshold);
        clock_t end_quick = clock();    //�� ���� ���� �ð� ���� ����

        //print_list(list_quick, data); //�� ���� ��� ���
        //�� ���� ���� �ð� ���
        printf("�ҿ� �ð�: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);
    }
    else if (type == 3) {
        printf("������ ���� ��\n");

        int i;
        int threshold;

        //�ʱ� ������ ����
        for (i = 0; i < data; i++) {
            list_merge[i] = i + 1;
            list_quick[i] = i + 1;
        }
        //�������� ��ġ�� �������� ����
        shuffle(list_merge, data);

        //���� �����͸� ����ϱ� ���� ����
        for (i = 0; i < data; i++)   list_quick[i] = list_merge[i];

        printf("������ ���� �Ϸ�\n");
        /*printf("\n������ ���\n");
        print_list(list_merge, data); //������ ���
        print_list(list_quick, data); //������ ���*/

        //�պ� ���� ����
        printf("\n�պ����� ����\n");

        clock_t start_merge = clock();  //�պ� ���� ���� �ð� ���� ����
        merge_sort_DC(list_merge, 0, data - 1);
        clock_t end_merge = clock();    //�պ� ���� ���� �ð� ���� ����

        //print_list(list_merge, data); //�պ� ���� ��� ���

        //�պ� ���� ���� �ð� ���
        printf("�ҿ� �ð�: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);

        free(list_merge);               //�պ� ���� �迭 �޸� �Ҵ� ����

        printf("�Ӱ谪�� �����Ͻÿ�. : ");
        scanf("%ld", &threshold);

        //�� ���� ����
        printf("\n������ ����\n");
        printf("�Ǻ� : %d\n", list_quick[0]);     //�Ǻ� ���

        clock_t start_quick = clock();            //�� ���� ���� �ð� ���� ����
        quicksort_DC(list_quick, 0, data - 1, threshold);
        clock_t end_quick = clock();    //�� ���� ���� �ð� ���� ����

        //print_list(list_quick, data); //�� ���� ��� ���
        //�� ���� ���� �ð� ���
        printf("�ҿ� �ð�: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);

        free(list_quick);           //�� ���� �迭 �޸� �Ҵ� ����

        return 0;
    }
    else {
        printf("error");
    }

    free(list_merge);           //�պ� ���� �迭 �޸� �Ҵ� ����
    free(list_quick);           //�� ���� �迭 �޸� �Ҵ� ����

    return 0;
}