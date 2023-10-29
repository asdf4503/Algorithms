#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100                //�׷����� �ִ� ũ�� ����
#define INF 99999999                //���Ѵ� ���� ��Ÿ���� ���

typedef struct Edge {               //���Ḯ��Ʈ ����� ���� Edge struct ����
    int u;
    int w;
    struct Edge* Link;              //���Ḯ��Ʈ ���� Edge Link (������)
} Edge;

typedef struct Graph {              //Graph struct ����
    int node;
    Edge* head[MAX_SIZE];           //��������Ʈ(adj_list)
} Graph;

typedef struct HeapNode {           //HeapNode struct ����
    int v;                          
    int d;
} HeapNode;

typedef struct Heap {               //Heap struct ����
    HeapNode data[MAX_SIZE];        //HeapNode�� data �迭 ����
    int size;
} Heap;

void init_graph(Graph* g) {         //�׷��� �ʱ�ȭ �Լ�
    int i = 0;
    g->node = 0;
    for (; i < MAX_SIZE; i++)
        g->head[i] = NULL;          //MAX_SIZE��ŭ �׷��� �ʱ�ȭ
}

void init_heap(Heap* heap) {        //�� �ʱ�ȭ �Լ�
    heap->size = 0;
}

void swapHeapNode(HeapNode* parent, HeapNode* child) {      //HeapNode�� ��ġ�� �����ϴ� �Լ�
    HeapNode etc = *parent;
    *parent = *child;
    *child = etc;
}

int isEmpty(Heap* heap) {           //���� ����ִ��� Ȯ���ϴ� �Լ�
    return heap->size == 0;
}

HeapNode delete_min_heap(Heap* heap) {                  //������ �ּҰ� ���� �Լ�
    HeapNode minNode = heap->data[0];                   //�ּҰ� ��� ����
    heap->data[0] = heap->data[heap->size - 1];         //������ ��带 ��Ʈ�� �̵�
    heap->size--;                                       //�� ũ�� ����

    // �� ������ ����
    int idx = 0;
    while (2 * idx + 1 < heap->size) {
        int child;
        if (2 * idx + 2 == heap->size) {
            child = 2 * idx + 1;
        }
        else {
            child = (heap->data[2 * idx + 1].d < heap->data[2 * idx + 2].d) ? 2 * idx + 1 : 2 * idx + 2;
        }

        if (heap->data[idx].d <= heap->data[child].d) {
            break;
        }

        swapHeapNode(&heap->data[idx], &heap->data[child]); //�θ�� �ڽ� ��� ��ġ ��ȯ
        idx = child;                                        //�ڽ� ���� �̵�
    }
    return minNode;                                         //�ּҰ� ��ȯ
}

void decreaseKey(Heap* heap, int v, int d) {                //������ Ư�� ����� ����ġ �� ���� �Լ�
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->data[i].v == v) {
            heap->data[i].d = d;                            //����ġ �� ����
            while (i != 0 && heap->data[i].d < heap->data[(i - 1) / 2].d) { // ����ġ ���� ����� ��带 �ùٸ� ��ġ�� �̵�
                swapHeapNode(&heap->data[i], &heap->data[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
            return;
        }
    }
}

void insert_min_heap(Heap* heap, int v, int d) {            //�ּ� �� ��� �߰� �Լ�
    int i = heap->size++;
    while (i != 0 && d < heap->data[(i - 1) / 2].d) {       //�� ����� ��ġ�� ã�� �̵�
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i].v = v;
    heap->data[i].d = d;                                    // ��� ���� ����
}

void addEdge(Graph* g, int idx, int u, int w) {             //�� ������ ����� ���� �� ����ġ �Է�
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));            //Edge �޸� ���� �Ҵ�
    newEdge->u = u;
    newEdge->w = w;
    newEdge->Link = g->head[idx];                           //Edge�� ���� ����Ʈ �տ� �߰�
    g->head[idx] = newEdge;                                 //head ����

    printf("%d -> %d   |   ����ġ ��: %2d |\n", idx, u, w);    // ��� ���� �߰�
}

void prim_MST(Graph* g) {                                   //���� �˰��� �Լ�
    int parent[MAX_SIZE];
    int key[MAX_SIZE];
    Heap heap;
    init_heap(&heap);
    int src = 0;
    int totalWeight = 0;                                    //prim_MST�� ��ü ����ġ ���� ������ ����

    for (int i = 0; i < g->node; i++) {
        key[i] = INF;
        insert_min_heap(&heap, i, INF);                     //��� ��带 ���� �߰�
    }

    key[src] = 0;
    decreaseKey(&heap, src, 0);                             //���� ����� ����ġ ���� 0���� ����

    printf("---------prim_MST START!!---------\n\n");

    while (!isEmpty(&heap)) {                               //prime ���� ����
        int u = delete_min_heap(&heap).v;

        Edge* edge = g->head[u];
        while (edge) {
            int v = edge->u;
            if (key[v] > edge->w) {
                int oldKey = key[v]; // ���� key �� ����
                key[v] = edge->w;
                decreaseKey(&heap, v, edge->w);
                parent[v] = u;

                // ����� key ���� ���� ������ �Բ� ���
                printf("(%d, %d) - ����ġ: %d | ", parent[v], v, key[v]);
                printf("���� %d�� key���� %d���� %d�� ����\n", v, oldKey, key[v]);
            }
            edge = edge->Link;
        }
    }

    printf("\n");

    for (int i = 1; i < g->node; i++) {                     //prim_MST�� ������ ��ü ����ġ ���
        printf("%d -> %d   |   ����ġ �� :  %d\n", parent[i], i, key[i]);
        totalWeight += key[i];                              //����ġ ���� totalWeight�� ����
    }

    printf("\n��ü ����ġ ���� : %d\n", totalWeight);                //��ü ����ġ �� ���
}

int main() {
    Heap heap;
    init_heap(&heap);       //�� �ʱ�ȭ

    Graph graph;
    init_graph(&graph);     //�׷��� �ʱ�ȭ

    graph.node = 9;         //�׷����� ���� ����

    printf("--------�׷��� ����---------\n");
    //�׷����� �� ���� ������ ����ġ �� �Է�
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
    printf("---------------------------\n");
    printf("\n\n");

    prim_MST(&graph);   //�Է� ���� �׷����� prim_MST ����

    return 0;
}