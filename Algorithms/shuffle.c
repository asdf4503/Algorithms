#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

void shuffle(int *list, int num) {      //배열을 무작위로 섞는 함수
    srand(time(NULL));                  //시드 값 설정

    int temp, data;                     //임시 저장 변수와 난수 저장 변수
    for (int i = 0; i < num; i++) {     //데이터의 갯수(num)만큼 반복 실행
        data = rand() % (num - i) + i;  //i 부터 num 사이에 임의의 정수 생성
        //배열 위치 변경
        temp = list[i];                 
        list[i] = list[data];
        list[data] = temp;
    }
}

void print_list(int *list, int num) {   //배열 출력 함수
    for (int i = 0; i < num; i++) {     //데이터의 갯수(num)만큼 반복 실행
        printf("%d ", list[i]);         //배열 출력
    }
    printf("\n");
}