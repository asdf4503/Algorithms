#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct Edge {			//연결리스트 사용을 위한 Edge struct 생성
	int u; //정점
	int w; //가중치
	struct Edge* Link;			//연결리스트 다음 Edge Link (포인터)
} Edge;

typedef struct Graph {			//Graph struct 생성
	//int node; //?
	Edge* head[MAX_SIZE];		//인접리스트
} Graph;

typedef struct Heap {			//Heap struct 생성
	Heap heap[MAX_SIZE];		//Heap 생성
	int size;
} Heap;

void init_graph(Graph* g) {		//그래프 초기화 함수
	int i = 0;
	//g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE만큼 그래프 초기화
}

void init_heap(Heap* heap) {	//힙 초기화 함수
	heap->size = 0;
}


void addEdge() {
	Edge* newEdge = (Edge*)malloc(sizeof(Edge)); //Edge에 메모리 동적 할당
}

void delete_min_heap() {

}

void decrease_key() {

}

void prim_MST(Graph* g, int u, int w) {

}


int main() {
	Heap heap;
	init_heap(&heap); //heap 초기화
}