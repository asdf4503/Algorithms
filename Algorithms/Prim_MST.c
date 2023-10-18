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
	Edge* head[MAX_SIZE];		//인접리스트(adj_list)
} Graph;

typedef struct Heap {			//Heap struct 생성
	HeapNode data[MAX_SIZE];	//HeapNode의 data 배열 생성
	int size;
} Heap;

typedef struct HeapNode {		//HeapNode struct 생성
	int v;						//
	int d;						//
} HeapNode;

void init_graph(Graph *g) {		//그래프 초기화 함수
	int i = 0;
	g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE만큼 그래프 초기화
}

void init_heap(Heap *heap) {	//힙 초기화 함수
	heap->size = 0;
}

void swapHeapNode(HeapNode *parent, HeapNode *child) {		//HeapNode의 위치를 변경하는 함수
	HeapNode etc = *parent;
	*parent = *child;
	*child = etc;
}


void addEdge(Graph *g, int idx, int u, int w) {				//각 정점과 연결된 정점 및 가중치 입력
	Edge* newEdge = (Edge *)malloc(sizeof(Edge));	//Edge 메모리 동적 할당
	newEdge->u = u;
	newEdge->w = w;
	newEdge->Link = g->head[idx];
	g->head[idx] = newEdge;
}

void insert_min_heap(HeapNode *heapNode) {					//최소 힙 추가 함수
	Heap* heap = (Heap*)malloc(sizeof(Heap));		//heap 메모리 할당

	if (heap == NULL)	return NULL;				//heap이 없다면 NULL 반환


}

void delete_min_heap() {	//최소 힙 삭제 함수

}

void decrease_key(Heap *heap, int u, int w) {		//가중치 값 변경 함수

}

void prim_MST(Graph *g, int u, int w) {		//prim algorithm

}


int main() {
	Heap heap;
	init_heap(&heap);		//heap 초기화
	
	Graph graph;
	init_graph(&graph);		//graph 초기화

	graph.node = 9;
	
	/*그래프 생성*/
	addEdge(&graph, 0, 1, 4);
	addEdge(&graph, 0, 7, 8);
	addEdge(&graph, 1, 2, 8);
	addEdge(&graph, 1, 7, 11);
	addEdge(&graph, 2, 3, 7);
	addEdge(&graph, 2, 5, 4);
	addEdge(&graph, 2, 8, 2);
	addEdge(&graph, 3, 4, 9);
	addEdge(&graph, 3, 5, 14);
	addEdge(&graph, 4, 5, 10);
	addEdge(&graph, 5, 6, 2);
	addEdge(&graph, 6, 7, 1);
	addEdge(&graph, 6, 8, 6);
	addEdge(&graph, 7, 8, 7);
}