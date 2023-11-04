#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100                //그래프의 최대 크기 정의
#define INF 999999999               //무한대 값을 나타내는 상수

typedef struct Edge {               //연결리스트 사용을 위한 Edge struct 생성
    int u;                          //정점
    int w;                          //가중치
    struct Edge* Link;              //연결리스트 다음 Edge Link (포인터)
} Edge;

typedef struct Graph {              //Graph struct 생성
    int node;                       //그래프 정점 개수
    Edge* head[MAX_SIZE];           //인접리스트(adj_list)
} Graph;

typedef struct HeapNode {           //HeapNode struct 생성
    int v;                          //정점
    int d;                          //거리
} HeapNode;

typedef struct Heap {               //Heap struct 생성
    HeapNode data[MAX_SIZE];        //HeapNode의 data 배열 생성
    int size;                       //Heap의 크기
} Heap;

void init_graph(Graph* g) {         //그래프 초기화 함수
    int i = 0;
    g->node = 0;
    for ( ; i < MAX_SIZE; i++)
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

HeapNode delete_min_heap(Heap* heap) {                  //힙에서 최소값 추출 함수
    HeapNode minNode = heap->data[0];                   //최소값 노드 저장
    heap->data[0] = heap->data[heap->size - 1];         //마지막 노드를 루트로 이동
    heap->size--;                                       //힙 크기 감소

    // 힙 재정렬 시작
    int idx = 0;                                        //루트에서 시작
    while (2 * idx + 1 < heap->size) {                  //현재 노드의 왼쪽 자식 idx가 힙 크기보다 작을 동안 반복
        int child;                                      //자식 노드의 idx를 저장할 변수
        if (2 * idx + 2 == heap->size) {                //오른쪽 자식이 없는 경우
            child = 2 * idx + 1;                        //왼쪽 자식 idx 저장
        }
        else {                                          //왼쪽, 오른쪽 자식이 모두 있는 경우
            //왼쪽과 오른쪽 자식 중 더 작은 값을 가진 자식의 idx 저장
            child = (heap->data[2 * idx + 1].d < heap->data[2 * idx + 2].d) ? 2 * idx + 1 : 2 * idx + 2;
        }

        //현재 노드의 값이 자식 노드의 값보다 작거나 같으면 종료
        if (heap->data[idx].d <= heap->data[child].d) {
            break;
        }

        swapHeapNode(&heap->data[idx], &heap->data[child]); //현재 노드와 자식 노드 위치 교환
        idx = child;                                        //idx를 자식 노드의 idx로 이동
    }
    return minNode;                                         //최솟값 반환
}

void decrease_key(Heap* heap, int v, int d) {                //힙에서 특정 노드의 가중치 값 변경 함수
    int i;
    for (i = 0; i < heap->size; i++) {                      //힙의 모든 노드를 순회
        if (heap->data[i].v == v) {                         //찾고자 하는 노드를 찾으면
            heap->data[i].d = d;                            //가중치 값 갱신
            while (i != 0 && heap->data[i].d < heap->data[(i - 1) / 2].d) { //가중치 값이 변경된 노드의 위치 조정
                swapHeapNode(&heap->data[i], &heap->data[(i - 1) / 2]);     //부모 노드와 비교하여, 변경된 노드의 가중치 값이 작으면 부모 노드와 위치 교환
                i = (i - 1) / 2;                            //index를 부모 노드의 index로 갱신
            }
            return;
        }
    }
}

void insert_min_heap(Heap* heap, int v, int d) {            //최소 힙 노드 추가 함수
    int i = heap->size++;                                   //노드를 추가할 위치를 힙의 마지막으로 설정
    while (i != 0 && d < heap->data[(i - 1) / 2].d) {       //새 노드의 위치를 찾아 이동
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i].v = v;                                    //노드 정점 정보 저장
    heap->data[i].d = d;                                    //노드 가중치 정보 저장
}

void addEdge(Graph* g, int idx, int u, int w) {             //각 정점과 연결된 정점 및 가중치 입력(무방향 그래프)
    Edge* newEdge1 = (Edge*)malloc(sizeof(Edge));           //Edge 메모리 동적 할당
    newEdge1->u = u;                                        //간선의 끝 정점 설정
    newEdge1->w = w;                                        //간선의 가중치 설정
    newEdge1->Link = g->head[idx];                          //Edge를 인접 리스트 앞에 추가
    g->head[idx] = newEdge1;                                //head 갱신

    Edge* newEdge2 = (Edge*)malloc(sizeof(Edge));           //Edge 메모리 동적 할당
    newEdge2->u = idx;                                      //간선의 끝 정점 설정
    newEdge2->w = w;                                        //간선의 가중치 설정
    newEdge2->Link = g->head[u];                            //Edge를 인접 리스트 앞에 추가
    g->head[u] = newEdge2;                                  //head 갱신

    printf("%d -> %d   |   가중치 값: %2d |\n", idx, u, w); // 출력 구문 추가
}

void prim_MST(Graph *g, Heap *heap, int root) {         //prim 알고리즘을 사용하여 최소 신장 트리를 찾는 함수
    int nearest[MAX_SIZE];                              //각 정점의 부모 정점을 저장하는 배열
    int distance[MAX_SIZE];                             //각 정점까지의 최단 거리를 저장하는 배열
    bool MST_v[MAX_SIZE];                               // 각 정점이 MST에 포함되었는지 여부를 저장하는 배열
    
    int src = root;                                     //시작 정점 번호
    int totalWeight = 0;                                //최소 신장 트리의 총 가중치 값

    int i;
    for (i = 0; i < g->node; i++) {
        distance[i] = INF;                              //초기 모든 노드의 거리를 무한대로 설정
        nearest[i] = src;                               // 모든 정점의 가장 가까운 연결 정점을 시작 정점으로 설정
        insert_min_heap(heap, i, INF);                  //힙에 모든 정점 추가
        MST_v[i] = false;                               //모든 정점을 prim_MST에 포함되지 않은 상태로 초기화
    }

    int visit[MAX_SIZE];          // 방문 순서를 저장하는 배열
    int orderCount = 0;           // 방문한 노드의 수를 카운트하는 변수

    for (i = 0; i < g->node; i++) {     //방문 순서 배열을 그래프의 노드 만큼 반복
        visit[i] = -1;            //방문 순서 배열을 -1로 초기화
    }

    visit[orderCount++] = src;   //시작 정점을 첫 번째 방문한 것으로 설정

    distance[src] = 0;                                  //시작 노드의 거리를 0으로 설정
    decrease_key(heap, src, 0);                         //시작 노드의 거리 갱신

    printf("---------prim_MST START!!---------\n\n");

    int count = 0;                                     //반복 횟수 카운트
    while (count <= g->node - 2) {                      //힙이 비어있지 않고, n(정점 수)-2 반복
        int u = delete_min_heap(heap).v;                //최솟값 추출
        MST_v[u] = true;                                //u 정점을 prim_MST에 포함시킴
        
        if (u != src)   visit[orderCount++] = u; //시작 정점이 아닌 경우 방문 순서 배열에 추가
        else            count--;                        //시작 정점 제외
        
        Edge* edge = g->head[u];                        //현재 정점의 인접 리스트
        while (edge) {                                  //인접 리스트 순회
            int v = edge->u;                            //인접 정점
            
            if (MST_v[v] == false && distance[v] > edge->w) {                //인접 정점까지의 거리(가중치)가 현재 가중치보다 클 경우
                int oldKey = distance[v];               //현재 거리 저장
                distance[v] = edge->w;                  //거리 갱신
                decrease_key(heap, v, edge->w);         //힙에서 정점의 거리 갱신
                nearest[v] = u;                         //부모 정점 갱신

                //가중치 값 변경 출력
                printf("정점 %d에서 정점 %d로의 가중치 확인 - 현재 가중치: %d, 인접 가중치: %d\n", u, v, distance[v], edge->w);
                printf("(%d, %d) - 가중치: %d | 정점 %d의 가중치 값이 %d에서 %d로 변경\n\n", nearest[v], v, distance[v], v, oldKey, distance[v]);
            }
            edge = edge->Link;                          //다음 인접 정점으로 이동
        }
        count++;                                        //카운트 증가
    }

    printf("\n--------prim_MST Result--------\n\n");

    //최소 신장 트리의 각 간선과 가중치 출력(시작 정점 제외)
    for (i = 0; i < orderCount; i++) {
        int u = visit[i];
        if (u != src) { //시작 정점 제외
            printf("%d -> %d   |   가중치 값 :  %d\n", nearest[u], u, distance[u]);
            totalWeight += distance[u]; //최소 가중치 합
        }
    }

    printf("\n---------prim_MST END!!---------\n");
    printf("\n전체 가중치 값은 : %d\n", totalWeight);  //최소 가중치 값 출력 구문
}

int main() {
    Graph graph;
    init_graph(&graph);     //그래프 초기화

    graph.node = 9;         //그래프의 정점 개수

    printf("--------그래프 생성---------\n");
    //그래프의 각 노드와 간선의 가중치 값 입력
    addEdge(&graph, 0, 1, 4);           //0 -> 1 가중치 : 4
    addEdge(&graph, 0, 7, 8);           //0 -> 7 가중치 : 8
    addEdge(&graph, 1, 2, 8);           //1 -> 2 가중치 : 8
    addEdge(&graph, 1, 7, 11);          //1 -> 7 가중치 : 11
    addEdge(&graph, 2, 3, 7);           //2 -> 3 가중치 : 7
    addEdge(&graph, 2, 5, 4);           //2 -> 5 가중치 : 4
    addEdge(&graph, 2, 8, 2);           //2 -> 8 가중치 : 2
    addEdge(&graph, 3, 4, 9);           //3 -> 4 가중치 : 9
    addEdge(&graph, 3, 5, 14);          //3 -> 5 가중치 : 14
    addEdge(&graph, 4, 5, 10);          //4 -> 5 가중치 : 10
    addEdge(&graph, 5, 6, 2);           //5 -> 6 가중치 : 2
    addEdge(&graph, 6, 7, 1);           //6 -> 7 가중치 : 1
    addEdge(&graph, 6, 8, 6);           //6 -> 8 가중치 : 6
    addEdge(&graph, 7, 8, 7);           //7 -> 8 가중치 : 7
    printf("---------------------------\n");
    printf("\n\n");

    bool chk = true;    //반복문 체크 변수

    while (chk) {       //프림 알고리즘이 한번 실행될 때까지 반복
        int root;       //시작 정점
        printf("시작 정점을 입력하세요 (0 ~ %d) : ", graph.node - 1);
        scanf_s("%d", &root); //시작 정점 입력

        //주어진 정점 이외 다른 정점 입력 시
        if (root < 0 || root >= graph.node)
            printf("올바르지 않은 정점 번호입니다.\n\n");
            
        else {
            Heap heap;
            init_heap(&heap);   //힙 초기화

            prim_MST(&graph, &heap, root);   //그래프 및 힙 초기화 후 prim_MST 실행
            chk = false;
        }
    }

    //메모리 할당 해제
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