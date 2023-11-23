#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "shuffle.h"
#include "quicksort.h"
#include "shuffle.h"

int main(void) {
    int index;
    int *list_merge;
    int *list_quick;
    
    printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
    scanf("%d", &index);
    list_merge = (int*)malloc(sizeof(int) * index);
    list_quick = (int*)malloc(sizeof(int) * index);

    int i;
    for (i = 0; i < index; i++) {
        list_merge[i] = i + 1;
        list_quick[i] = i + 1;
    }

    shuffle(list_merge, index);

    for (i = 0; i < index; i++) {
        list_quick[i] = list_merge[i];
    }

    //merge_sort ���� �ð� ����
    clock_t start_merge = clock();

    //merge_sort ����
    merge_sort_DC(list_merge, 0, index - 1);

    clock_t end_merge = clock();
    printf("�պ����� ���� : ");
    //print_list(list_merge, index);

    printf("�ҿ� �ð�: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);

    free(list_merge);

    clock_t start_quick = clock();
    //�� ���� ����
    printf("�Ǻ� : %d\n", list_quick[0]);
    quicksort_DC(list_quick, 0, index - 1, 0);

    clock_t end_quick = clock();
    printf("������ ���� : ");
    //print_list(list_quick, index);
    
    printf("�ҿ� �ð�: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);

    free(list_quick);

    return 0;
}
