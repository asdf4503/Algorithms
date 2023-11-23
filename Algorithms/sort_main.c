#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "shuffle.h"
#include "quicksort.h"
#include "shuffle.h"

int main(void) {
    int data;
    int *list_merge; //
    int *list_quick;
    
    printf("������ ������ �Է��Ͻÿ�. : ");
    scanf("%d", &data);
    list_merge = (int*)malloc(sizeof(int) * data);
    list_quick = (int*)malloc(sizeof(int) * data);

    int i;
    for (i = 0; i < data; i++) {
        list_merge[i] = i + 1;
        list_quick[i] = i + 1;
    }

    shuffle(list_merge, data);

    for (i = 0; i < data; i++) {
        list_quick[i] = list_merge[i];
    }

    //merge_sort ���� �ð� ����
    clock_t start_merge = clock();

    //merge_sort ����
    printf("�պ����� ����\n");
    merge_sort_DC(list_merge, 0, data - 1);

    clock_t end_merge = clock();
    //print_list(list_merge, data);

    printf("�ҿ� �ð�: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);

    free(list_merge);

    clock_t start_quick = clock();
    //�� ���� ����
    printf("������ ����\n");
    printf("�Ǻ� : %d\n", list_quick[0]);
    quicksort_DC(list_quick, 0, data - 1, 1000);

    clock_t end_quick = clock();
    //print_list(list_quick, data);
    
    printf("�ҿ� �ð�: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);

    free(list_quick);

    return 0;
}
