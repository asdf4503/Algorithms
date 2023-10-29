#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100                //그래프의 최대 크기 정의
#define INF 99999999                //무한대 값을 나타내는 상수

typedef struct Edge {               //연결리스트 사용을 위한 Edge struct 생성
    int u;
    int w;
    struct Edge* Link;              //연결리스트 다음 Edge Link (포인터)
} Edge;

typedef struct Graph {              //Graph struct 생성
    int node;
    Edge* head[MAX_SIZE];           //인접리스트(adj_list)
} Graph;

typedef struct HeapNode {           //HeapNode struct 생성
    int v;                          
    int d;
} HeapNode;

typedef struct Heap {               //Heap struct 생성
    HeapNode data[MAX_SIZE];        //HeapNode의 data 배열 생성
    int size;
} Heap;

void init_graph(Graph* g) {         //그래프 초기화 함수
    int i = 0;
    g->node = 0;
    for (; i < MAX_SIZE; i++)
        g->head[i] = NULL;          //MAX_SIZE만큼 그래프 초기화
}

void init_heap(Heap* heap) {        //힙 초기화 함수
    heap->size = 0;
}

void swapHeapNode(HeapNode* parent, HeapNode* child) {      //HeapNode의 위치를 변경하는 함수
    HeapNode etc = *parent;
    *parent = *child;
    *child = etc;
}

int isEmpty(Heap* heap) {           //힙이 비어있는지 확인하는 함수
    return heap->size == 0;
}

HeapNode delete_min_heap(Heap* heap) {                  //힙에서 최소값 추출 함수
    HeapNode minNode = heap->data[0];                   //최소값 노드 저장
    heap->data[0] = heap->data[heap->size - 1];         //마지막 노드를 루트로 이동
    heap->size--;                                       //힙 크기 감소

    // 힙 재정렬 시작
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

        swapHeapNode(&heap->data[idx], &heap->data[child]); //부모와 자식 노드 위치 교환
        idx = child;                                        //자식 노드로 이동
    }
    return minNode;                                         //최소값 반환
}

void decreaseKey(Heap* heap, int v, int d) {                //힙에서 특정 노드의 가중치 값 변경 함수
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->data[i].v == v) {
            heap->data[i].d = d;                            //가중치 값 갱신
            while (i != 0 && heap->data[i].d < heap->data[(i - 1) / 2].d) { // 가중치 값이 변경된 노드를 올바른 위치로 이동
                swapHeapNode(&heap->data[i], &heap->data[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
            return;
        }
    }
}

void insert_min_heap(Heap* heap, int v, int d) {            //최소 힙 노드 추가 함수
    int i = heap->size++;
    while (i != 0 && d < heap->data[(i - 1) / 2].d) {       //새 노드의 위치를 찾아 이동
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i].v = v;
    heap->data[i].d = d;                                    // 노드 정보 저장
}

void addEdge(Graph* g, int idx, int u, int w) {             //각 정점과 연결된 정점 및 가중치 입력
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));            //Edge 메모리 동적 할당
    newEdge->u = u;
    newEdge->w = w;
    newEdge->Link = g->head[idx];                           //Edge를 인접 리스트 앞에 추가
    g->head[idx] = newEdge;                                 //head 갱신

    printf("%d -> %d   |   가중치 값: %2d |\n", idx, u, w);    // 출력 구문 추가
}

void prim_MST(Graph* g) {                                   //프림 알고리즘 함수
    int parent[MAX_SIZE];
    int key[MAX_SIZE];
    Heap heap;
    init_heap(&heap);
    int src = 0;
    int totalWeight = 0;                                    //prim_MST의 전체 가중치 값을 저장할 변수

    for (int i = 0; i < g->node; i++) {
        key[i] = INF;
        insert_min_heap(&heap, i, INF);                     //모든 노드를 힙에 추가
    }

    key[src] = 0;
    decreaseKey(&heap, src, 0);                             //시작 노드의 가중치 값을 0으로 갱신

    printf("---------prim_MST START!!---------\n\n");

    while (!isEmpty(&heap)) {                               //prime 수행 시작
        int u = delete_min_heap(&heap).v;

        Edge* edge = g->head[u];
        while (edge) {
            int v = edge->u;
            if (key[v] > edge->w) {
                int oldKey = key[v]; // 이전 key 값 저장
                key[v] = edge->w;
                decreaseKey(&heap, v, edge->w);
                parent[v] = u;

                // 변경된 key 값과 간선 정보를 함께 출력
                printf("(%d, %d) - 가중치: %d | ", parent[v], v, key[v]);
                printf("정점 %d의 key값이 %d에서 %d로 변경\n", v, oldKey, key[v]);
            }
            edge = edge->Link;
        }
    }

    printf("\n");

    for (int i = 1; i < g->node; i++) {                     //prim_MST의 간선과 전체 가중치 출력
        printf("%d -> %d   |   가중치 값 :  %d\n", parent[i], i, key[i]);
        totalWeight += key[i];                              //가중치 값을 totalWeight에 더함
    }

    printf("\n전체 가중치 값은 : %d\n", totalWeight);                //전체 가중치 값 출력
}

int main() {
    Heap heap;
    init_heap(&heap);       //힙 초기화

    Graph graph;
    init_graph(&graph);     //그래프 초기화

    graph.node = 9;         //그래프의 정점 개수

    printf("--------그래프 생성---------\n");
    //그래프의 각 노드와 간선의 가중치 값 입력
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

    prim_MST(&graph);   //입력 받은 그래프로 prim_MST 실행

    return 0;
}