#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

struct heap{
    int size, array_size;
    int *key, *val;
}printer[1000100];

void push(struct heap* pq, int pri, int id){
    if (pq->size == pq->array_size){
        if (pq->size == 0) pq->array_size = 1;
        else pq->array_size *= 2;
        int *tmp1 = (int*) malloc(sizeof(int) * (pq->array_size+1)), *tmp2 = (int*) malloc(sizeof(int) * (pq->array_size+1));
        for (int i=1;i<=pq->size;++i){
            tmp1[i] = pq->key[i];
            tmp2[i] = pq->val[i];
        }
        free(pq->key);
        free(pq->val);
        pq->key = tmp1;
        pq->val = tmp2;
    }

    ++pq->size;
    pq->key[pq->size] = pri;
    pq->val[pq->size] = id;
    int cur = pq->size;
    while (cur > 1 && pq->key[cur] > pq->key[cur/2]){
        swap(pq->key+cur, pq->key+cur/2);
        swap(pq->val+cur, pq->val+cur/2);
        cur /= 2;
    }
}

int pop(struct heap* pq){
    if (pq->size == 0) return -1;
    int ret = pq->val[1];

    pq->key[1] = pq->key[pq->size];
    pq->val[1] = pq->val[pq->size];
    --pq->size;
    int cur = 1;
    while (1){
        int swap_to = cur;

        if (cur*2 <= pq->size && pq->key[cur*2] > pq->key[swap_to]) swap_to = cur*2;
        if (cur*2+1 <= pq->size && pq->key[cur*2+1] > pq->key[swap_to]) swap_to = cur*2+1;

        if (swap_to == cur) break;
        else{
            swap(pq->key+cur, pq->key+swap_to);
            swap(pq->val+cur, pq->val+swap_to);
            cur = swap_to;
        }
    }
    return ret;
}

void merge(struct heap* h1, struct heap* h2){
    int swapped = 0;
    if (h1->size > h2->size){
        struct heap* tmp = h1;
        h1 = h2;
        h2 = tmp;
        swapped = 1;
    }
    for (int i=1;i<=h1->size;++i) push(h2, h1->key[i], h1->val[i]);
    free(h1->key);
    free(h1->val);
    if (swapped){
        h1->size = h2->size;
        h2->size = 0;
        h1->array_size = h2->array_size;
        h2->array_size = 0;
        h1->key = h2->key;
        h2->key = NULL;
        h1->val = h2->val;
        h2->val = NULL;
    }
    else{
        h1->size = 0;
        h1->array_size = 0;
        h1->key = NULL;
        h1->val = NULL;
    }
}

int main(){
    int n, m;

    scanf("%d%d", &n, &m);
    for (int i=1;i<=n;++i){
        printer[i].size = 0;
        printer[i].key = printer[i].val = NULL;
    }
    while (m--){
        int op;

        scanf("%d", &op);
        if (op == 1){
            int jid, pri, pid;

            scanf("%d%d%d", &jid, &pri, &pid);
            push(printer+pid, pri, jid);
            printf("%d jobs waiting on printer %d\n", printer[pid].size, pid);
        }
        else if (op == 2){
            int pid;

            scanf("%d", &pid);
            int p = pop(printer+pid);
            if (p != -1) printf("%d printed\n", p);
            else printf("no documents in queue\n");
        }
        else{
            int p1, p2;

            scanf("%d%d", &p1, &p2);
            merge(printer+p1, printer+p2);
            printf("%d jobs waiting on printer %d after moving\n", printer[p2].size, p2);
        }
    }
}
