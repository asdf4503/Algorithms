#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Edge {			//연결리스트 사용을 위한 Edge struct 생성
	int u; //정점
	int w; //가중치
	struct Edge* Link;			//연결리스트 다음 Edge Link (포인터)
} Edge;

typedef struct Graph {			//Graph struct 생성
	int node;
	Edge* head[MAX_SIZE];		//인접리스트
} Graph;

typedef struct Heap {			//Heap struct 생성
	Heap heap[MAX_SIZE];		//Heap 생성
	int size;
} Heap;

void init_graph(Graph* g) {		//그래프 초기화 함수
	int i = 0;
	g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE만큼 그래프 초기화
}

void init_heap(Heap* heap) {	//힙 초기화 함수
	heap->size = 0;
}


void addEdge(Graph *g, int idx, int u, int w) {				//각 정점과 연결된 정점 및 가중치 입력
	Edge* newEdge = (Edge*)malloc(sizeof(Edge));	//Edge에 메모리 동적 할당
	newEdge->u = u;
	newEdge->w = w;
	newEdge->Link = g->head[idx];
	g->head[idx] = newEdge;
}

void insert_min_heap() {	//최소 힙 추가 함수

}

void delete_min_heap() {	//최소 힙 삭제 함수

}

void decrease_key() {		//가중치 값 변경 함수

}

void prim_MST(Graph* g, int u, int w) {		//prim algorithm

}


int main() {
	Heap heap;
	init_heap(&heap); //heap 초기화
}