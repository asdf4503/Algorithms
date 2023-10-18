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
	Edge* head[MAX_SIZE];		//��������Ʈ(adj_list)
} Graph;

typedef struct Heap {			//Heap struct ����
	HeapNode data[MAX_SIZE];	//HeapNode�� data �迭 ����
	int size;
} Heap;

typedef struct HeapNode {		//HeapNode struct ����
	int v;						//
	int d;						//
} HeapNode;

void init_graph(Graph *g) {		//�׷��� �ʱ�ȭ �Լ�
	int i = 0;
	g->node = 0;
	for (; i < MAX_SIZE; i++)
		g->head[i] = NULL;		//MAX_SIZE��ŭ �׷��� �ʱ�ȭ
}

void init_heap(Heap *heap) {	//�� �ʱ�ȭ �Լ�
	heap->size = 0;
}

void swapHeapNode(HeapNode *parent, HeapNode *child) {		//HeapNode�� ��ġ�� �����ϴ� �Լ�
	HeapNode etc = *parent;
	*parent = *child;
	*child = etc;
}


void addEdge(Graph *g, int idx, int u, int w) {				//�� ������ ����� ���� �� ����ġ �Է�
	Edge* newEdge = (Edge *)malloc(sizeof(Edge));	//Edge �޸� ���� �Ҵ�
	newEdge->u = u;
	newEdge->w = w;
	newEdge->Link = g->head[idx];
	g->head[idx] = newEdge;
}

void insert_min_heap(HeapNode *heapNode) {					//�ּ� �� �߰� �Լ�
	Heap* heap = (Heap*)malloc(sizeof(Heap));		//heap �޸� �Ҵ�

	if (heap == NULL)	return NULL;				//heap�� ���ٸ� NULL ��ȯ


}

void delete_min_heap() {	//�ּ� �� ���� �Լ�

}

void decrease_key(Heap *heap, int u, int w) {		//����ġ �� ���� �Լ�

}

void prim_MST(Graph *g, int u, int w) {		//prim algorithm

}


int main() {
	Heap heap;
	init_heap(&heap);		//heap �ʱ�ȭ
	
	Graph graph;
	init_graph(&graph);		//graph �ʱ�ȭ

	graph.node = 9;
	
	/*�׷��� ����*/
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