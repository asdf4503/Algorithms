#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Edge {			//���Ḯ��Ʈ ����� ���� Edge struct ����
	int u; //����
	int w; //����ġ
	struct Edge* Link;			//���Ḯ��Ʈ ���� Edge Link (������)
} Edge;

typedef struct Graph {			//Graph struct ����
	int node;
	Edge* head[MAX_SIZE];		//��������Ʈ
} Graph;

typedef struct Heap {			//Heap struct ����
	Heap heap[MAX_SIZE];		//Heap ����
	int size;
} Heap;

void init_graph(Graph* g) {		//�׷��� �ʱ�ȭ �Լ�
	int i = 0;
	g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE��ŭ �׷��� �ʱ�ȭ
}

void init_heap(Heap* heap) {	//�� �ʱ�ȭ �Լ�
	heap->size = 0;
}


void addEdge(Graph *g, int idx, int u, int w) {				//�� ������ ����� ���� �� ����ġ �Է�
	Edge* newEdge = (Edge*)malloc(sizeof(Edge));	//Edge�� �޸� ���� �Ҵ�
	newEdge->u = u;
	newEdge->w = w;
	newEdge->Link = g->head[idx];
	g->head[idx] = newEdge;
}

void insert_min_heap() {	//�ּ� �� �߰� �Լ�

}

void delete_min_heap() {	//�ּ� �� ���� �Լ�

}

void decrease_key() {		//����ġ �� ���� �Լ�

}

void prim_MST(Graph* g, int u, int w) {		//prim algorithm

}


int main() {
	Heap heap;
	init_heap(&heap); //heap �ʱ�ȭ
}