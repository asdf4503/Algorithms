#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct Edge {			//���Ḯ��Ʈ ����� ���� Edge struct ����
	int u; //����
	int w; //����ġ
	struct Edge* Link;			//���Ḯ��Ʈ ���� Edge Link (������)
} Edge;

typedef struct Graph {			//Graph struct ����
	//int node; //?
	Edge* head[MAX_SIZE];		//��������Ʈ
} Graph;

typedef struct Heap {			//Heap struct ����
	Heap heap[MAX_SIZE];		//Heap ����
	int size;
} Heap;

void init_graph(Graph* g) {		//�׷��� �ʱ�ȭ �Լ�
	int i = 0;
	//g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE��ŭ �׷��� �ʱ�ȭ
}

void init_heap(Heap* heap) {	//�� �ʱ�ȭ �Լ�
	heap->size = 0;
}


void addEdge() {
	Edge* newEdge = (Edge*)malloc(sizeof(Edge)); //Edge�� �޸� ���� �Ҵ�
}

void delete_min_heap() {

}

void decrease_key() {

}

void prim_MST(Graph* g, int u, int w) {

}


int main() {
	Heap heap;
	init_heap(&heap); //heap �ʱ�ȭ
}