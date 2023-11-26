#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "shuffle.h"
#include "quicksort.h"
#include "shuffle.h"

void start() {
    int data;           //데이터 갯수를 저장하는 변수
    int* list_merge;    //합병 정렬에 사용될 배열 포인터
    int* list_quick;    //퀵 정렬에 사용될 배열 포인터
    int type = 0;

    printf("20191480 신용선\n");
    //데이터 입력
    printf("데이터 갯수를 입력하시오. : ");
    scanf("%d", &data);
    printf("\n");

    //데이터를 저장할 배열 할당
    list_merge = (int*)malloc(sizeof(int) * data);
    list_quick = (int*)malloc(sizeof(int) * data);

    //정렬 프로그램 선택
    printf("합병 정렬 : 1 / 퀵 정렬 : 2 / 모두 : 3\n");
    printf("어떤 프로그램을 실행하시겠습니까? : ");
    scanf("%d", &type);

    //선택에 맞는 프로그램 실행
    if (type == 1) {
        printf("\n데이터 생성 중\n");
        int i;
        //초기 데이터 생성
        for (i = 0; i < data; i++)      list_merge[i] = i + 1;
        //데이터의 위치를 무작위로 섞음
        shuffle(list_merge, data);
        printf("데이터 생성 완료\n");
        /*//데이터 출력
        printf("\n데이터 출력\n");
        print_list(list_merge, data); //데이터 출력*/

        //합병 정렬 시작
        printf("\n합병정렬 실행\n");

        clock_t start_merge = clock();  //합병 정렬 실행 시간 측정 시작
        merge_sort_DC(list_merge, 0, data - 1);
        clock_t end_merge = clock();    //합병 정렬 실행 시간 측정 종료

        //print_list(list_merge, data); //합병 정렬 결과 출력

        //합병 정렬 실행 시간 출력
        printf("소요 시간: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);
    }
    else if (type == 2) {
        printf("\n데이터 생성 중\n");

        int i;
        long threshold;

        //초기 데이터 생성
        for (i = 0; i < data; i++)      list_quick[i] = i + 1;
        //데이터의 위치를 무작위로 섞음
        shuffle(list_quick, data);
        printf("데이터 생성 완료\n");
        //데이터 출력
        /*printf("\n데이터 출력\n");
        print_list(list_quick, data);*/

        printf("\n임계값을 설정하시오. : ");
        scanf("%ld", &threshold);

        //퀵 정렬 시작
        printf("퀵정렬 실행\n");
        printf("피봇 : %d\n", list_quick[0]);     //피봇 출력

        clock_t start_quick = clock();            //퀵 정렬 실행 시간 측정 시작
        quicksort_DC(list_quick, 0, data - 1, threshold);
        clock_t end_quick = clock();    //퀵 정렬 실행 시간 측정 종료

        //print_list(list_quick, data); //퀵 정렬 결과 출력
        //퀵 정렬 실행 시간 출력
        printf("소요 시간: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);
    }
    else if (type == 3) {
        printf("데이터 생성 중\n");

        int i;
        int threshold;

        //초기 데이터 생성
        for (i = 0; i < data; i++) {
            list_merge[i] = i + 1;
            list_quick[i] = i + 1;
        }
        //데이터의 위치를 무작위로 섞음
        shuffle(list_merge, data);

        //같은 데이터를 사용하기 위한 복사
        for (i = 0; i < data; i++)   list_quick[i] = list_merge[i];

        printf("데이터 생성 완료\n");
        /*printf("\n데이터 출력\n");
        print_list(list_merge, data); //데이터 출력
        print_list(list_quick, data); //데이터 출력*/

        //합병 정렬 시작
        printf("\n합병정렬 실행\n");

        clock_t start_merge = clock();  //합병 정렬 실행 시간 측정 시작
        merge_sort_DC(list_merge, 0, data - 1);
        clock_t end_merge = clock();    //합병 정렬 실행 시간 측정 종료

        //print_list(list_merge, data); //합병 정렬 결과 출력

        //합병 정렬 실행 시간 출력
        printf("소요 시간: %lf\n\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);

        free(list_merge);               //합병 정렬 배열 메모리 할당 해제

        printf("임계값을 설정하시오. : ");
        scanf("%ld", &threshold);

        //퀵 정렬 시작
        printf("\n퀵정렬 실행\n");
        printf("피봇 : %d\n", list_quick[0]);     //피봇 출력

        clock_t start_quick = clock();            //퀵 정렬 실행 시간 측정 시작
        quicksort_DC(list_quick, 0, data - 1, threshold);
        clock_t end_quick = clock();    //퀵 정렬 실행 시간 측정 종료

        //print_list(list_quick, data); //퀵 정렬 결과 출력
        //퀵 정렬 실행 시간 출력
        printf("소요 시간: %lf\n\n", (double)(end_quick - start_quick) / CLOCKS_PER_SEC);

        free(list_quick);           //퀵 정렬 배열 메모리 할당 해제

        return 0;
    }
    else {
        printf("error");
    }

    free(list_merge);           //합병 정렬 배열 메모리 할당 해제
    free(list_quick);           //퀵 정렬 배열 메모리 할당 해제

    return 0;
}