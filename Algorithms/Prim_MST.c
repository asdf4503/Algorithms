#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100                //�׷����� �ִ� ũ�� ����
#define INF 999999999               //���Ѵ� ���� ��Ÿ���� ���

typedef struct Edge {               //���Ḯ��Ʈ ����� ���� Edge struct ����
    int u;                          //����
    int w;                          //����ġ
    struct Edge* Link;              //���Ḯ��Ʈ ���� Edge Link (������)
} Edge;

typedef struct Graph {              //Graph struct ����
    int node;                       //�׷��� ���� ����
    Edge* head[MAX_SIZE];           //��������Ʈ(adj_list)
} Graph;

typedef struct HeapNode {           //HeapNode struct ����
    int v;                          //����
    int d;                          //�Ÿ�
} HeapNode;

typedef struct Heap {               //Heap struct ����
    HeapNode data[MAX_SIZE];        //HeapNode�� data �迭 ����
    int size;                       //Heap�� ũ��
} Heap;

void init_graph(Graph* g) {         //�׷��� �ʱ�ȭ �Լ�
    int i = 0;
    g->node = 0;
    for ( ; i < MAX_SIZE; i++)
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

HeapNode delete_min_heap(Heap* heap) {                  //������ �ּҰ� ���� �Լ�
    HeapNode minNode = heap->data[0];                   //�ּҰ� ��� ����
    heap->data[0] = heap->data[heap->size - 1];         //������ ��带 ��Ʈ�� �̵�
    heap->size--;                                       //�� ũ�� ����

    // �� ������ ����
    int idx = 0;                                        //��Ʈ���� ����
    while (2 * idx + 1 < heap->size) {                  //���� ����� ���� �ڽ� idx�� �� ũ�⺸�� ���� ���� �ݺ�
        int child;                                      //�ڽ� ����� idx�� ������ ����
        if (2 * idx + 2 == heap->size) {                //������ �ڽ��� ���� ���
            child = 2 * idx + 1;                        //���� �ڽ� idx ����
        }
        else {                                          //����, ������ �ڽ��� ��� �ִ� ���
            //���ʰ� ������ �ڽ� �� �� ���� ���� ���� �ڽ��� idx ����
            child = (heap->data[2 * idx + 1].d < heap->data[2 * idx + 2].d) ? 2 * idx + 1 : 2 * idx + 2;
        }

        //���� ����� ���� �ڽ� ����� ������ �۰ų� ������ ����
        if (heap->data[idx].d <= heap->data[child].d) {
            break;
        }

        swapHeapNode(&heap->data[idx], &heap->data[child]); //���� ���� �ڽ� ��� ��ġ ��ȯ
        idx = child;                                        //idx�� �ڽ� ����� idx�� �̵�
    }
    return minNode;                                         //�ּڰ� ��ȯ
}

void decrease_key(Heap* heap, int v, int d) {                //������ Ư�� ����� ����ġ �� ���� �Լ�
    int i;
    for (i = 0; i < heap->size; i++) {                      //���� ��� ��带 ��ȸ
        if (heap->data[i].v == v) {                         //ã���� �ϴ� ��带 ã����
            heap->data[i].d = d;                            //����ġ �� ����
            while (i != 0 && heap->data[i].d < heap->data[(i - 1) / 2].d) { //����ġ ���� ����� ����� ��ġ ����
                swapHeapNode(&heap->data[i], &heap->data[(i - 1) / 2]);     //�θ� ���� ���Ͽ�, ����� ����� ����ġ ���� ������ �θ� ���� ��ġ ��ȯ
                i = (i - 1) / 2;                            //index�� �θ� ����� index�� ����
            }
            return;
        }
    }
}

void insert_min_heap(Heap* heap, int v, int d) {            //�ּ� �� ��� �߰� �Լ�
    int i = heap->size++;                                   //��带 �߰��� ��ġ�� ���� ���������� ����
    while (i != 0 && d < heap->data[(i - 1) / 2].d) {       //�� ����� ��ġ�� ã�� �̵�
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i].v = v;                                    //��� ���� ���� ����
    heap->data[i].d = d;                                    //��� ����ġ ���� ����
}

void addEdge(Graph* g, int idx, int u, int w) {             //�� ������ ����� ���� �� ����ġ �Է�(������ �׷���)
    Edge* newEdge1 = (Edge*)malloc(sizeof(Edge));           //Edge �޸� ���� �Ҵ�
    newEdge1->u = u;                                        //������ �� ���� ����
    newEdge1->w = w;                                        //������ ����ġ ����
    newEdge1->Link = g->head[idx];                          //Edge�� ���� ����Ʈ �տ� �߰�
    g->head[idx] = newEdge1;                                //head ����

    Edge* newEdge2 = (Edge*)malloc(sizeof(Edge));           //Edge �޸� ���� �Ҵ�
    newEdge2->u = idx;                                      //������ �� ���� ����
    newEdge2->w = w;                                        //������ ����ġ ����
    newEdge2->Link = g->head[u];                            //Edge�� ���� ����Ʈ �տ� �߰�
    g->head[u] = newEdge2;                                  //head ����

    printf("%d -> %d   |   ����ġ ��: %2d |\n", idx, u, w); // ��� ���� �߰�
}

void prim_MST(Graph *g, Heap *heap, int root) {         //prim �˰����� ����Ͽ� �ּ� ���� Ʈ���� ã�� �Լ�
    int nearest[MAX_SIZE];                              //�� ������ �θ� ������ �����ϴ� �迭
    int distance[MAX_SIZE];                             //�� ���������� �ִ� �Ÿ��� �����ϴ� �迭
    bool MST_v[MAX_SIZE];                               // �� ������ MST�� ���ԵǾ����� ���θ� �����ϴ� �迭
    
    int src = root;                                     //���� ���� ��ȣ
    int totalWeight = 0;                                //�ּ� ���� Ʈ���� �� ����ġ ��

    int i;
    for (i = 0; i < g->node; i++) {
        distance[i] = INF;                              //�ʱ� ��� ����� �Ÿ��� ���Ѵ�� ����
        nearest[i] = src;                               // ��� ������ ���� ����� ���� ������ ���� �������� ����
        insert_min_heap(heap, i, INF);                  //���� ��� ���� �߰�
        MST_v[i] = false;                               //��� ������ prim_MST�� ���Ե��� ���� ���·� �ʱ�ȭ
    }

    int visit[MAX_SIZE];          // �湮 ������ �����ϴ� �迭
    int orderCount = 0;           // �湮�� ����� ���� ī��Ʈ�ϴ� ����

    for (i = 0; i < g->node; i++) {     //�湮 ���� �迭�� �׷����� ��� ��ŭ �ݺ�
        visit[i] = -1;            //�湮 ���� �迭�� -1�� �ʱ�ȭ
    }

    visit[orderCount++] = src;   //���� ������ ù ��° �湮�� ������ ����

    distance[src] = 0;                                  //���� ����� �Ÿ��� 0���� ����
    decrease_key(heap, src, 0);                         //���� ����� �Ÿ� ����

    printf("---------prim_MST START!!---------\n\n");

    int count = 0;                                     //�ݺ� Ƚ�� ī��Ʈ
    while (count <= g->node - 2) {                      //���� ������� �ʰ�, n(���� ��)-2 �ݺ�
        int u = delete_min_heap(heap).v;                //�ּڰ� ����
        MST_v[u] = true;                                //u ������ prim_MST�� ���Խ�Ŵ
        
        if (u != src)   visit[orderCount++] = u; //���� ������ �ƴ� ��� �湮 ���� �迭�� �߰�
        else            count--;                        //���� ���� ����
        
        Edge* edge = g->head[u];                        //���� ������ ���� ����Ʈ
        while (edge) {                                  //���� ����Ʈ ��ȸ
            int v = edge->u;                            //���� ����
            
            if (MST_v[v] == false && distance[v] > edge->w) {                //���� ���������� �Ÿ�(����ġ)�� ���� ����ġ���� Ŭ ���
                int oldKey = distance[v];               //���� �Ÿ� ����
                distance[v] = edge->w;                  //�Ÿ� ����
                decrease_key(heap, v, edge->w);         //������ ������ �Ÿ� ����
                nearest[v] = u;                         //�θ� ���� ����

                //����ġ �� ���� ���
                printf("���� %d���� ���� %d���� ����ġ Ȯ�� - ���� ����ġ: %d, ���� ����ġ: %d\n", u, v, distance[v], edge->w);
                printf("(%d, %d) - ����ġ: %d | ���� %d�� ����ġ ���� %d���� %d�� ����\n\n", nearest[v], v, distance[v], v, oldKey, distance[v]);
            }
            edge = edge->Link;                          //���� ���� �������� �̵�
        }
        count++;                                        //ī��Ʈ ����
    }

    printf("\n--------prim_MST Result--------\n\n");

    //�ּ� ���� Ʈ���� �� ������ ����ġ ���(���� ���� ����)
    for (i = 0; i < orderCount; i++) {
        int u = visit[i];
        if (u != src) { //���� ���� ����
            printf("%d -> %d   |   ����ġ �� :  %d\n", nearest[u], u, distance[u]);
            totalWeight += distance[u]; //�ּ� ����ġ ��
        }
    }

    printf("\n---------prim_MST END!!---------\n");
    printf("\n��ü ����ġ ���� : %d\n", totalWeight);  //�ּ� ����ġ �� ��� ����
}

int main() {
    Graph graph;
    init_graph(&graph);     //�׷��� �ʱ�ȭ

    graph.node = 9;         //�׷����� ���� ����

    printf("--------�׷��� ����---------\n");
    //�׷����� �� ���� ������ ����ġ �� �Է�
    addEdge(&graph, 0, 1, 4);           //0 -> 1 ����ġ : 4
    addEdge(&graph, 0, 7, 8);           //0 -> 7 ����ġ : 8
    addEdge(&graph, 1, 2, 8);           //1 -> 2 ����ġ : 8
    addEdge(&graph, 1, 7, 11);          //1 -> 7 ����ġ : 11
    addEdge(&graph, 2, 3, 7);           //2 -> 3 ����ġ : 7
    addEdge(&graph, 2, 5, 4);           //2 -> 5 ����ġ : 4
    addEdge(&graph, 2, 8, 2);           //2 -> 8 ����ġ : 2
    addEdge(&graph, 3, 4, 9);           //3 -> 4 ����ġ : 9
    addEdge(&graph, 3, 5, 14);          //3 -> 5 ����ġ : 14
    addEdge(&graph, 4, 5, 10);          //4 -> 5 ����ġ : 10
    addEdge(&graph, 5, 6, 2);           //5 -> 6 ����ġ : 2
    addEdge(&graph, 6, 7, 1);           //6 -> 7 ����ġ : 1
    addEdge(&graph, 6, 8, 6);           //6 -> 8 ����ġ : 6
    addEdge(&graph, 7, 8, 7);           //7 -> 8 ����ġ : 7
    printf("---------------------------\n");
    printf("\n\n");

    bool chk = true;    //�ݺ��� üũ ����

    while (chk) {       //���� �˰����� �ѹ� ����� ������ �ݺ�
        int root;       //���� ����
        printf("���� ������ �Է��ϼ��� (0 ~ %d) : ", graph.node - 1);
        scanf_s("%d", &root); //���� ���� �Է�

        //�־��� ���� �̿� �ٸ� ���� �Է� ��
        if (root < 0 || root >= graph.node)
            printf("�ùٸ��� ���� ���� ��ȣ�Դϴ�.\n\n");
            
        else {
            Heap heap;
            init_heap(&heap);   //�� �ʱ�ȭ

            prim_MST(&graph, &heap, root);   //�׷��� �� �� �ʱ�ȭ �� prim_MST ����
            chk = false;
        }
    }

    //�޸� �Ҵ� ����
    for (int i = 0; i < graph.node; i++) {
        Edge* current = graph.head[i];
        while (current) {
            Edge* temp = current;
            current = current->Link;
            free(temp);
        }
    }

    return 0;
}