#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000001
#define MAX_M 1000001

typedef struct binomial_node {
    int key;
    int id;
    int degree;
    struct binomial_node *parent;
    struct binomial_node *child; // pointer of first child
    struct binomial_node *sibling;
} BinomialNode;

BinomialNode *MakeBinomialHeap() {
    return NULL;
}

int BinomialHeapMaximum(BinomialNode* H){
    binomial_node* temp = H;
    binomial_node* max_node = NULL; // the node with maximum
    int max = -1; // maximum
    while(temp != NULL){
        if(temp->key > max){
            max_node = temp;
            max = temp->key;
        }
        temp = temp->sibling;
    }
    return max;
}

void BinomialLink(BinomialNode* y, BinomialNode* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree += 1;
    return;
}

BinomialNode *BinomialHeapMerge(BinomialNode* H1, BinomialNode* H2){
    if (H1 == NULL) return H2;
    if (H2 == NULL) return H1;

    BinomialNode *head = NULL;
    BinomialNode *tail = NULL;
    BinomialNode *temp;

    while (H1 != NULL && H2 != NULL) {
        if (H1->degree <= H2->degree) {
            temp = H1;
            H1 = H1->sibling;
        } 
        else {
            temp = H2;
            H2 = H2->sibling;
        }

        if (head == NULL) {
            head = temp;
            tail = temp;
        } 
        else {
            tail->sibling = temp;
            tail = temp;
        }
    }

    if (H1 != NULL) tail->sibling = H1;
    else tail->sibling = H2;

    return head;
}

BinomialNode *BinomialHeapUnion(BinomialNode* H1, BinomialNode* H2){
    BinomialNode *H = BinomialHeapMerge(H1, H2);
    if(H == NULL) return H;
    BinomialNode *prev = NULL;
    BinomialNode *curr = H;
    BinomialNode *next = curr->sibling;
    while(next != NULL){
        if((curr->degree != next->degree) || (next->sibling != NULL && curr->degree == next->sibling->degree)){
            prev = curr;
            curr = next;
        }
        else{
            if(curr->key > next->key){
                curr->sibling = next->sibling;
                BinomialLink(next, curr);
            }
            else{
                if(prev == NULL){
                    H = next;
                }
                else{
                    prev->sibling = next;
                }
                BinomialLink(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return H;
}

BinomialNode *BinomialHeapInsert(BinomialNode* H, int key, int id){
    BinomialNode *new_node = (BinomialNode *)malloc(sizeof(BinomialNode));
    new_node->key = key;
    new_node->id = id;
    new_node->degree = 0;
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->sibling = NULL;
    H = BinomialHeapUnion(H, new_node);
    return H;
}

BinomialNode *BinomialHeapExtractMax(BinomialNode* H){
    if(H == NULL){
        printf("no documents in queue\n");
        return H;
    }
    binomial_node* temp = H;
    binomial_node* prev = NULL;
    binomial_node* max_node = NULL; // the node with maximum
    binomial_node* max_prev = NULL; // the node before max_node
    int max = -1; // maximum
    while(temp != NULL){
        if(temp->key > max){
            max_prev = prev;
            max_node = temp;
            max = temp->key;
        }
        prev = temp;
        temp = temp->sibling;
    }

    printf("%d printed\n", max_node->id);
    
    // remove max_node from the root list of H
    if(max_prev != NULL) max_prev->sibling = max_node->sibling;
    else H = H->sibling;

    // reverse child linked list of min_node
    prev = NULL;
    BinomialNode* curr = max_node->child;
    BinomialNode* next = NULL;

    while(curr != NULL){
        next = curr->sibling;
        curr->sibling = prev;
        prev = curr;
        curr = next;
    }

    max_node->child = prev;

    H = BinomialHeapUnion(H, max_node->child);
    return H;
}

void PrintBinomialHeap(BinomialNode* H){
    if (H == NULL) return;

    BinomialNode *curr = H;
    printf("(");
    while(curr != NULL){
        printf("B%d: ", curr->degree);
        printf("%d ", curr->key);
        PrintBinomialHeap(curr->child);
        curr = curr->sibling;
    }
    printf(")");
}

typedef struct Printer{
    BinomialNode *heap;
    int count;
}printer;

printer P[MAX_N];

int main(){

    int N, M;
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++){
        P[i].heap = MakeBinomialHeap();
        P[i].count = 0;
    }
    for(int i = 0; i < M; i++){
        int op = 0;
        scanf("%d", &op);
        if(op == 1){
            int job_id, priority, printer_id;
            scanf("%d%d%d", &job_id, &priority, &printer_id);
            // printf("add %d %d %d\n", job_id, priority, printer_id);
            P[printer_id].heap = BinomialHeapInsert(P[printer_id].heap, priority, job_id);
            P[printer_id].count += 1;
            printf("%d jobs waiting on printer %d\n", P[printer_id].count, printer_id);
        }
        else if(op == 2){
            int printer_id;
            scanf("%d", &printer_id);
            // printf("print %d\n", printer_id);
            P[printer_id].heap = BinomialHeapExtractMax(P[printer_id].heap);
            if(P[printer_id].count > 0) P[printer_id].count -= 1;
        }
        else{
            int printer_id1, printer_id2;
            scanf("%d%d", &printer_id1, &printer_id2);
            // printf("move %d %d\n", printer_id1, printer_id2);
            P[printer_id2].heap = BinomialHeapUnion(P[printer_id1].heap, P[printer_id2].heap);
            P[printer_id1].heap = MakeBinomialHeap();
            P[printer_id2].count += P[printer_id1].count;
            P[printer_id1].count = 0;
            printf("%d jobs waiting on printer %d after moving\n", P[printer_id2].count, printer_id2);
        }
    }
    return 0;
}
