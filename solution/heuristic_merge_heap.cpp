#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000001
#define MAX_M 1000001

typedef struct heap_node {
    int key;
    int id;
} HeapNode;

typedef struct Printer{
    HeapNode *arr;
    int heap_size;
    int count;
}printer;

printer P[MAX_N];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int printer_id, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && P[printer_id].arr[index].key > P[printer_id].arr[parent].key) {
        HeapNode tmp_N = P[printer_id].arr[index];
        P[printer_id].arr[index] = P[printer_id].arr[parent];
        P[printer_id].arr[parent] = tmp_N;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert(int printer_id, int key, int id) {
    if (P[printer_id].heap_size == P[printer_id].count){
        P[printer_id].arr = (HeapNode *)realloc(P[printer_id].arr, (2 * P[printer_id].heap_size) * sizeof(HeapNode));
        P[printer_id].heap_size *= 2;
    }
    P[printer_id].arr[P[printer_id].count].key = key;
    P[printer_id].arr[P[printer_id].count].id = id;
    P[printer_id].count += 1;
    heapifyUp(printer_id, P[printer_id].count - 1);
}

void heapifyDown(int printer_id, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int max = index;

    if (left < P[printer_id].count && P[printer_id].arr[left].key > P[printer_id].arr[max].key) {
        max = left;
    }

    if (right < P[printer_id].count && P[printer_id].arr[right].key > P[printer_id].arr[max].key) {
        max = right;
    }

    if (max != index) {
        HeapNode tmp_N = P[printer_id].arr[index];
        P[printer_id].arr[index] = P[printer_id].arr[max];
        P[printer_id].arr[max] = tmp_N;
        heapifyDown(printer_id, max);
    }
}

HeapNode extractMax(int printer_id) { // return id
    if (P[printer_id].count == 0) {
        HeapNode tmp_N = {-1, -1};
        return tmp_N;
    }

    HeapNode tmp_N = P[printer_id].arr[0];
    P[printer_id].arr[0] = P[printer_id].arr[P[printer_id].count - 1];
    P[printer_id].count -= 1;
    heapifyDown(printer_id, 0);
    return tmp_N;
}

void printHeap(int printer_id) {
    printf("Heap elements: ");
    for (int i = 0; i < P[printer_id].count; i++) {
        printf("key = %d, id = %d\n", P[printer_id].arr[i].key, P[printer_id].arr[i].id);
    }
    printf("\n");
}

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++){
        P[i].arr = (HeapNode *)malloc(1 * sizeof(HeapNode));
        P[i].heap_size = 1;
        P[i].count = 0;
    }
    for(int i = 0; i < M; i++){
        int op = 0;
        scanf("%d", &op);
        if(op == 1){
            int job_id, priority, printer_id;
            scanf("%d%d%d", &job_id, &priority, &printer_id);
            // printf("add %d %d %d\n", job_id, priority, printer_id);
            insert(printer_id, priority, job_id);
            printf("%d jobs waiting on printer %d\n", P[printer_id].count, printer_id);
        }
        else if(op == 2){
            int printer_id;
            scanf("%d", &printer_id);
            // printf("print %d\n", printer_id);
            HeapNode re = extractMax(printer_id);
            if(re.key == -1) printf("no documents in queue\n");
            else printf("%d printed\n", re.id);
        }
        else{
            int printer_id1, printer_id2;
            scanf("%d%d", &printer_id1, &printer_id2);
            // printf("move %d %d\n", printer_id1, printer_id2);
            int swap = 0;
            if(P[printer_id1].count > P[printer_id2].count){
                int tmp = printer_id1;
                printer_id1 = printer_id2;
                printer_id2 = tmp;
                swap = 1;
            }
            while(1){
                HeapNode re = extractMax(printer_id1);
                if(re.key == -1) break;
                insert(printer_id2, re.key, re.id);
            }
            if(swap == 1){
                printer tmp_P = P[printer_id1];
                P[printer_id1] = P[printer_id2];
                P[printer_id2] = tmp_P;
                printer_id2 = printer_id1;
            }
            printf("%d jobs waiting on printer %d after moving\n", P[printer_id2].count, printer_id2);
        }
    }
    return 0;
}
